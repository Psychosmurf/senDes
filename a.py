from Tkinter import *
import database as db


class SSR(object):
    ''' Class for senior design gui '''
    def __init__(self, master):
        self.master = master
        self.master.geometry('800x480+0+0')
        master.title("Smart Skateboard Rack")
        # Base frames
        self.top_frame = Frame(master, width=800, height=130, bg="gray78")
        self.top_frame.place(x=0, y=0)
        self.top_frame.pack_propagate(False)

        self.mid_lframe = Frame(self.master, width=400, height=300, bg="gray")
        self.mid_lframe.place(x=0, y=130)
        self.mid_lframe.pack_propagate(False)

        self.mid_rframe = Frame(self.master, width=400, height=300, bg="blue")
        self.mid_rframe.place(x=400, y=130)
        self.mid_rframe.pack_propagate(False)

        self.bot_frame = Frame(master, width=800, height=50, bg="gray78")
        self.bot_frame.place(x=0, y=430)
        self.bot_frame.pack_propagate(False)
        # Labels
        font = ('calibri', 30, 'bold')
        texth = "Smart Skateboard Rack\nWelcome!"
        heading = Label(self.top_frame, font=font, text=texth, fg="black", bg="gray78")
        heading.pack()

        fontb = ('arial', 20, 'italic')
        textb = "Already a user? Just scan below to get started"
        bottom = Label(self.bot_frame, font=fontb, text=textb, fg="black", bg="gray78")
        bottom.pack()
        # Buttons
        self.new_button = Button(self.mid_lframe, font=font, text="New User", command=self.new_user)
        self.new_button.config(height=100, width=100, bg="PaleTurquoise3")
        self.new_button.pack()

        text = "Manual Log In"
        self.man_button = Button(self.mid_rframe, font=font, text=text, command=self.man_login)
        self.man_button.config(height=100, width=100, bg="dark sea green")
        self.man_button.pack()

        self.username = Entry()
        self.password = Entry()
        self.email = Entry()
        self.user_text = Label()
        self.pass_text = Label()
        self.email_text = Label()
        self.reg_text = Label()
        self.cred = 0

    def new_user(self):
        ''' Signs up a new user '''
        nu_frame = Frame(self.master, width=800, height=480, bg="PaleTurquoise3")
        nu_frame.place(x=0, y=0)
        nu_frame.pack_propagate(False)

        font = ('Calibri', 25, 'bold')
        text = "Register"
        message = Label(nu_frame, font=font, text=text, bg="PaleTurquoise3", fg="black", )
        message.place(x=350, y=50)

        self.reg_text = Label(nu_frame, text="Please fill out all fields", bg="PaleTurquoise3")
        self.reg_text.place(x=365, y=140)

        self.email = Entry(nu_frame)
        self.email.place(x=350, y=170)
        self.email_text = Label(nu_frame, text="       Email:", bg="PaleTurquoise3")
        self.email_text.place(x=275, y=170)


        self.username = Entry(nu_frame)
        self.username.place(x=350, y=200)
        self.user_text = Label(nu_frame, text="Username:", bg="PaleTurquoise3")
        self.user_text.place(x=275, y=200)


        self.password = Entry(nu_frame)
        self.password.place(x=350, y=230)
        self.pass_text = Label(nu_frame, text=" Password:", bg="PaleTurquoise3")
        self.pass_text.place(x=275, y=230)

        submit = Button(nu_frame, text="Submit", command=lambda: self.enter_user(nu_frame))
        submit.place(x=350, y=260)

        back = Button(nu_frame, text="Go Back", command=nu_frame.destroy)
        back.place(x=25, y=430)

    def enter_user(self, frame):
        ''' Enter a new a user into database '''
        user = self.username.get()
        pas = self.password.get()
        email = self.email.get()

        (val, txt) = db.enter_user(user, pas, email)

        if val == 1:
            print "new account created"
            frame.destroy()
        else:
            font = ('Calibri', 20, 'bold')
            text = txt
            message = Label(frame, font=font, text=text, bg="red", fg="white", )
            message.place(x=200 + val, y=300)



    def man_login(self):
        ''' User logs inf they already have an account '''
        man_frame = Frame(self.master, width=800, height=480, bg="dark sea green")
        man_frame.place(x=0, y=0)
        man_frame.pack_propagate(False)

        font = ('Calibri', 25, 'bold')
        text = "Log In"
        message = Label(man_frame, font=font, text=text, bg="dark sea green", fg="black", )
        message.place(x=350, y=50)

        self.username = Entry(man_frame)
        self.username.place(x=350, y=200)
        self.user_text = Label(man_frame, text="Username:", bg="dark sea green")
        self.user_text.place(x=275, y=200)


        self.password = Entry(man_frame)
        self.password.place(x=350, y=230)
        self.pass_text = Label(man_frame, text=" Password:", bg="dark sea green")
        self.pass_text.place(x=275, y=230)

        submit = Button(man_frame, text="Submit", command=lambda: self.check_credentials(man_frame))
        submit.place(x=350, y=260)

        back = Button(man_frame, text="Go Back", command=man_frame.destroy)
        back.place(x=25, y=430)

        self.cred = 0



    def check_credentials(self, frame):
        ''' checks credentials '''
        user = self.username.get()
        pas = self.password.get()
        message = Label()

        state = db.check_user(user, pas)
        if state:
            print "success"
            self.cred = 0
            frame.destroy()
        else:
            if not self.cred:
                font = ('Calibri', 20, 'bold')
                text = "Incorrect credentials!"
                message = Label(frame, font=font, text=text, bg="red", fg="white", )
                message.place(x=260, y=150)
                self.cred = 1


ROOT = Tk()
MY_GUI = SSR(ROOT)
ROOT.mainloop()
