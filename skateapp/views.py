from django.shortcuts import render
from django.http import HttpResponse, Http404
from skateapp.forms import UserDataForm
from . models import UserData

def index(request):
    return render (request, "skateApp/templates/index.html", {})

def signup(request):
    if request.method == "POST":
        userData = UserDataForm(request.POST)
        if userData.is_valid():
            print ("user data is valid")
            name = userData.cleaned_data['username']
            password = userData.cleaned_data['password']
            email = userData.cleaned_data['email']
            if UserData.objects.filter(name=name):
                return render (request, "skateApp/templates/ErrorUserExists.html", {})
            else:
                user = UserData.objects.create(name = name,
                                               password = password,
                                               email = email,
                                               loggedIn = 0)
                user.save()
                return render (request, "skateApp/templates/RegistrationSuccess.html", {})
        else:
            return render (request, "skateApp/templates/ErrorFieldsNotValid.html", {})


    return render (request, "skateApp/templates/signup.html", {})



def login(request):
    if request.method == "POST":
        userData = UserDataForm(request.POST)
        if userData.is_valid():
            print ("user data is valid")
            username = userData.cleaned_data['username']
            userpass = userData.cleaned_data['password']
            useremail = userData.cleaned_data['email']
            if UserData.objects.filter(name=username, password=userpass, email=useremail):
                udb = UserData.objects.filter(name=username, password=userpass, email=useremail)
                for u in udb:
                    u.loggedIn = 1
                    u.save()
                return render (request, "skateApp/templates/LoginSuccess.html", {})
            else:
                return render (request, "skateApp/templates/ErrorAuthFailure.html", {})
        else:
            return render (request, "skateApp/templates/ErrorFieldsNotValid.html", {})

    return render (request, "skateApp/templates/login.html", {})
