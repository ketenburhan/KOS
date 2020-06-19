package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"os"
)

type path []string

type _file struct {
	name       string
	startptr   uint32
	size       uint32
	contextptr *string
	parent     *_directory
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

	// readDictioary()
	dict.files = make([]*_file, 3)
	dict.files[0] = &_file{name: "index.html", parent: &dict}
	dict.files[1] = &_file{name: "style.css", parent: &dict}
	dict.files[2] = &_file{name: "script.js", parent: &dict}

	dict.files[0].setContext(`<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Document</title>
</head>
<body>
	
</body>
</html>`)
	dict.files[1].setContext("html, body { margin: 0px }")
	dict.files[2].setContext("alert('Hello World')")

	saveToDisk()
	// fmt.Fprintln(os.Stdout, getDirectory(path{"home", "document", "kos"}))
	// fmt.Fprintln(os.Stdout, getFile(path{"home", "documents", "three"}))

	// fmt.Fprintln(os.Stdout, string(dictionaryToBytes()))
	// fmt.Fprintln(os.Stdout, unsafe.Sizeof(dict))
}

func createFileToPath(p path) *_file {
	l := len(p)
	filename := p[l-1]
	p = p[:l-1]
	parent := getDirectory(p)
	return createFile(filename, parent)
}
func createFile(filename string, parent *_directory) *_file {
	file := &_file{name: filename}
	file.parent = parent
	parent.files = append(parent.files, file)
	return file
}
func createDirectoryToPath(p path) *_directory {
	l := len(p)
	dirname := p[l-1]
	p = p[:l-1]
	parent := getDirectory(p)
	return createDirectory(dirname, parent)
}
func createDirectory(dirname string, parent *_directory) *_directory {
	dir := &_directory{name: dirname}
	dir.parent = parent
	parent.directories = append(parent.directories, dir)
	return dir
}

func setContextByPath(p path, str string) bool {
	return getFile(p[:]).setContext(str)
}
func (file *_file) setContext(str string) bool {
	if file != nil {
		s := new(string)
		*s = str
		file.contextptr = s
		file.size = uint32(len(str))
		return true
	}
	return false
}

func getContextByPath(p path) string {
	return getFile(p[:]).getContext()
}
func (file *_file) getContext() string {
	if file != nil {
		if file.contextptr == nil {
			return string(read(file.startptr+contextPtr, file.size))
		}
		return *file.contextptr
	}
	return ""
}

func read(ptr, size uint32) []byte {

	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	buf := make([]byte, size)
	file.ReadAt(buf, int64(ptr)) // index, err
	file.Close()
	return buf
}

func getDirectory(p path) *_directory {
	var ptr *_directory = &dict
	for _, name := range p {
		oldptr := ptr
		for _, x := range ptr.directories {
			if x.name == name {
				ptr = x
				break
			}
		}
		if oldptr == ptr {
			return nil
		}
	}
	return ptr
}
func getFile(p path) *_file {
	l := len(p)
	filename := p[l-1]
	p = p[:l-1]
	ptr := getDirectory(p)
	for _, x := range ptr.files {
		if x.name == filename {
			return x
		}
	}
	return nil
}

func readDictioary() {
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	buf := make([]byte, 4)
	file.Read(buf) // index, err
	contextPtr = bytesToUint32(buf)
	// fmt.Fprintln(os.Stdout, buf)

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
func dictionaryToBytes() []byte {
	var value []byte = []byte(dict.name)
	for _, cdir := range dict.directories {
		value = append(value, cdir.toBytes()...)
	}
	for _, cfile := range dict.files {
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
func (file *_file) toBytes() []byte {
	var value []byte = []byte(file.name)
	value = append(value, 30)
	value = append(value, uint32ToBytes(file.startptr)...)
	fmt.Fprintln(os.Stdout, uint32ToBytes(file.startptr))
	value = append(value, uint32ToBytes(file.size)...)
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

func getFiles(dir *_directory) []*_file {
	var files []*_file
	files = append(files, dir.files...)
	for _, x := range dir.directories {
		files = append(files, getFiles(x)...)
	}
	return files
}

func saveToDisk() {
	var context []byte
	files := getFiles(&dict)
	for _, file := range files {
		fcontext := file.getContext()
		file.startptr = uint32(len(context))
		file.size = uint32(len(fcontext))
		file.contextptr = nil
		context = append(context, []byte(fcontext)...)
	}
	context = append(dictionaryToBytes(), context...)
	fmt.Fprintln(os.Stdout, string(context))
}
