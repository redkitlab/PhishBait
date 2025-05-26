package main

import (
	"fmt"
	"net/http"
	"os"
	"os/exec"
	"os/signal"
	"runtime"
	"syscall"
	"time"
)

const version = "v0.0.0"
var server *http.Server

func clearTerminal() {
	switch runtime.GOOS {
	case "windows":
		cmd := exec.Command("cmd", "/c", "cls")
		cmd.Stdout = os.Stdout
		cmd.Run()
	case "darwin":
		cmd := exec.Command("clear")
		cmd.Stdout = os.Stdout
		cmd.Run()
		fmt.Print("\033[3J")
	default:
		cmd := exec.Command("clear")
		cmd.Stdout = os.Stdout
		cmd.Run()
	}
}

func homeDisplay() int {
	clearTerminal()
	fmt.Printf(" ___ _    _    _    ___       _ _\n")
	fmt.Printf("| _ \\ |_ (_)__| |_ | _ ) __ _(_) |_\n")
	fmt.Printf("|  _/ ' \\| (_-< ' \\| _ \\/ _` | |  _|\n")
	fmt.Printf("|_| |_||_|_|__/_||_|___/\\__,_|_|\\__|  %s\n\n\n", version)
	fmt.Println("[0] Quit")
	fmt.Println("[1] Demo")
	fmt.Println("[2] Google")
	fmt.Print("\nSelect an option: ")

	var choice int
	for {
		_, err := fmt.Scan(&choice)
		if err == nil && choice >= 0 && choice <= 2 {
			break
		}
		fmt.Print("Not an option, try again: ")
	}
	return choice
}

func startServer() {
	fs := http.FileServer(http.Dir("TackleBox"))
	server = &http.Server{Addr: ":8080", Handler: fs}

	go func() {
		if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			fmt.Println("Server error:", err)
		}
	}()
	time.Sleep(2 * time.Second)
}

func killServer() {
	if server != nil {
		server.Close()
	}
}

func openFile(file string) {
	startServer()
	time.Sleep(2 * time.Second)

	url := "http://localhost:8080/" + file

	var cmd *exec.Cmd
	switch runtime.GOOS {
	case "windows":
		cmd = exec.Command("rundll32", "url.dll,FileProtocolHandler", url)
	case "darwin":
		cmd = exec.Command("open", url)
	default:
		cmd = exec.Command("xdg-open", url)
	}
	cmd.Start()
}

func main() {
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)
	go func() {
		<-c
		killServer()
		clearTerminal()
		os.Exit(0)
	}()

	for {
		choice := homeDisplay()
		switch choice {
		case 0:
			killServer()
			clearTerminal()
			return
		case 1:
			openFile("Demo/demo.html")
		case 2:
			openFile("Google/googlebait.html")
		}
	}
}
