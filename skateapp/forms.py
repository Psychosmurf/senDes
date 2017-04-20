from django import forms
from skateapp.models import UserData

class UserDataForm(forms.Form):
    username = forms.CharField(max_length = 100)
    password = forms.CharField(max_length = 100, widget = forms.PasswordInput())
    email = forms.CharField(max_length = 100)

    def getName(self):
        return self.username

    def getPass(self):
        return self.password

    def getEmail(self):
        return self.email
