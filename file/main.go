package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"os"
	"unsafe"
)

type path []string

type _file struct {
	name     string
	startptr uint32
	size     uint32
	parent   *_directory
}

type _directory struct {
	name        string
	directories []*_directory
	files       []*_file
	parent      *_directory
}

var contextPtr uint32
var dict _directory
var fileName string

func main() {
	fileName = "demo.file"

	readDictioary()

	fmt.Fprintln(os.Stdout, string(dictionaryToBytes(dict)))
	fmt.Fprintln(os.Stdout, unsafe.Sizeof(dict))
}
func readDictioary() {
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	buf := make([]byte, 4)
	file.Read(buf) // index, err
	contextPtr = bytesToUint32(buf)
	fmt.Fprintln(os.Stdout, buf)

	l := contextPtr - 4

	buf = make([]byte, l)
	file.ReadAt(buf, 4) // index, err
	file.Close()

	var ptr *_directory = &dict

	var placeholder []byte

	var i uint32 = 0
	for i < l {
		var b byte = buf[i]
		switch buf[i] {
		case 28: // {
			newDirectory := &_directory{name: string(placeholder), parent: ptr}
			ptr.directories = append(ptr.directories, newDirectory)
			// fmt.Fprintln(os.Stdout, "/", string(placeholder))
			if buf[i+1] == 29 {
				i++
			} else {
				ptr = newDirectory
			}
			placeholder = []byte{}
		case 29: // }
			ptr = ptr.parent
		case 30: // #
			ptr.files = append(ptr.files, &_file{
				name:     string(placeholder),
				startptr: bytesToUint32(buf[i+1 : i+5]),
				size:     bytesToUint32(buf[i+5 : i+9])})

			// fmt.Fprintln(os.Stdout, "*", string(placeholder), bytesToUint32(buf[i+1:i+5]), bytesToUint32(buf[i+5:i+9]))
			placeholder = []byte{}
			i += 8
		default: // any
			placeholder = append(placeholder, b)
		}
		i++
	}
}
func dictionaryToBytes(d _directory) []byte {
	var value []byte = []byte(d.name)
	for _, cdir := range d.directories {
		value = append(value, cdir.toBytes()...)
	}
	for _, cfile := range d.files {
		value = append(value, cfile.toBytes()...)
	}
	value = append(uint32ToBytes(uint32(len(value)+4)), value...)
	return value
}

func (d *_directory) toBytes() []byte {
	var value []byte = []byte(d.name)
	value = append(value, 28)
	for _, cdir := range d.directories {
		value = append(value, cdir.toBytes()...)
	}
	for _, cfile := range d.files {
		value = append(value, cfile.toBytes()...)
	}
	value = append(value, 29)
	return value
}
func (f *_file) toBytes() []byte {
	var value []byte = []byte(f.name)
	value = append(value, 30)
	value = append(value, uint32ToBytes(f.startptr)...)
	value = append(value, uint32ToBytes(f.size)...)
	return value
}

func bytesToUint32(bytes []byte) uint32 {
	return uint32(binary.LittleEndian.Uint32(bytes))
}
func uint32ToBytes(num uint32) []byte {
	a := make([]byte, 4)
	binary.LittleEndian.PutUint32(a, num)
	return a
}
