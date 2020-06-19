package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"os/exec"
	"strings"
)

type flag map[string]string

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("Hello KOS ❤\n\n")
	for {
		fmt.Printf("> ")
		input, _ := reader.ReadString('\n')
		run(input)
	}
}
func run(input string) {
	input = strings.TrimSuffix(input, "\n")
	input = strings.TrimSuffix(input, "\r")

	args := strings.Split(input, " ")

	switch args[0] {
	case "exit":
		os.Exit(0)
	case "asd":
		fmt.Printf("asd\n")
		return
	case "clear":
		clearScreen()
	case "cls":
		clearScreen()
	case "":
		return
	default:
		fmt.Fprintln(os.Stdout, "invalid command `"+args[0]+"`")
		return
	}
}
func clearScreen() {
	cmd := exec.Command("clear")
	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout
	if err := cmd.Run(); err != nil {
		log.Fatal(err)
	}
}

func input() string {
	return "asd"
}
