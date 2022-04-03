from tkinter import *

MainWindow = Tk()
from socket import *
import time

MainWindow.geometry("700x500")
clientSocket = socket(AF_INET, SOCK_DGRAM)


def UDP_Send(Message, IP, Port):
    clientSocket.sendto(Message.encode(), (IP, int(Port)))


HEIGHT = 500
WIDTH = 500
BACKGROUND = "#181818"
FOREGROUND = "#282828"
TEXTCOLOR = "#FFFFFF"
FRAMESIZE = 0.2

# IP
IP_Frame = Frame(MainWindow, bg=BACKGROUND, height=HEIGHT, width=WIDTH, bd=5)
IP_Frame.place(relx=0, rely=0, relwidth=1, relheight=.25)
IP_Label = Label(IP_Frame, text='Type that IP in >:):', bg=FOREGROUND, fg=TEXTCOLOR, bd=5, font=('Calibri', 20))
IP_Label.place(relx=0, rely=0, relwidth=0.5, relheight=1)
IP_Entry = Entry(IP_Frame, bg=FOREGROUND, bd=0, fg=TEXTCOLOR, font=('Calibri', 20))
IP_Entry.place(relx=0.51, rely=0, relwidth=0.5, relheight=1)

# Port
Port_Frame = Frame(MainWindow, bg=BACKGROUND, height=HEIGHT, width=WIDTH, bd=5)
Port_Frame.place(relx=0, rely=0.25, relwidth=1, relheight=.25)
Port_Label = Label(Port_Frame, text='port nuber lol:', bg=FOREGROUND, fg=TEXTCOLOR, bd=5, font=('Calibri', 20))
Port_Label.place(relx=0, rely=0, relwidth=0.5, relheight=1)
Port_Entry = Entry(Port_Frame, bg=FOREGROUND, bd=0, fg=TEXTCOLOR, font=('Calibri', 20))
Port_Entry.place(relx=0.51, rely=0, relwidth=0.5, relheight=1)

# UDP Commands
Command_Frame = Frame(MainWindow, bg=BACKGROUND, bd=5)
Command_Frame.place(relx=0, rely=.5, relwidth=1, relheight=.5)
Command_Button = Button(Command_Frame, bg=FOREGROUND, bd=0, fg=TEXTCOLOR, text='BING BONG',
                        font=('Calibri', 20), command=lambda: Command_Button.focus_set())
Command_Button.place(relwidth=1, relheight=1)
# Forwards
Command_Button.bind("w", (lambda event: UDP_Send('^F1', IP_Entry.get(), Port_Entry.get())))
# Left
Command_Button.bind("a", (lambda event: UDP_Send('^L', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("z", (lambda event: UDP_Send('^T2', IP_Entry.get(), Port_Entry.get())))

#45's
Command_Button.bind("q", (lambda event: UDP_Send('^E', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("e", (lambda event: UDP_Send('^Q', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("i", (lambda event: UDP_Send('^P', IP_Entry.get(), Port_Entry.get())))



# Reverse
Command_Button.bind("s", (lambda event: UDP_Send('^B1', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("x", (lambda event: UDP_Send('^PINRe3', IP_Entry.get(), Port_Entry.get())))

# Right
Command_Button.bind("d", (lambda event: UDP_Send('^R', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("c", (lambda event: UDP_Send('^PINRi4', IP_Entry.get(), Port_Entry.get())))

# Wheel Adjust
Command_Button.bind("i", (lambda event: UDP_Send('^PINLL+', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("k", (lambda event: UDP_Send('^PINLL-', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("o", (lambda event: UDP_Send('^PINRR+', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("l", (lambda event: UDP_Send('^PINRR-', IP_Entry.get(), Port_Entry.get())))
Command_Button.focus_set()

# Zone Reach and Stop
Command_Button.bind("<space>", (lambda event: UDP_Send('^U', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("1", (lambda event: UDP_Send('^K1', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("2", (lambda event: UDP_Send('^K2', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("3", (lambda event: UDP_Send('^K3', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("4", (lambda event: UDP_Send('^K4', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("5", (lambda event: UDP_Send('^K5', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("6", (lambda event: UDP_Send('^K6', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("7", (lambda event: UDP_Send('^K7', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("8", (lambda event: UDP_Send('^K8', IP_Entry.get(), Port_Entry.get())))
Command_Button.bind("9", (lambda event: UDP_Send('^K9', IP_Entry.get(), Port_Entry.get())))

MainWindow.mainloop()
