from django.db import models

class UserData(models.Model):
    name = models.CharField(max_length = 100)
    password = models.CharField(max_length = 100)
    email = models.CharField(max_length = 100)
    loggedIn = models.BooleanField(default = 0)
    def __str__(self):
        return "name: %s\npassword: %s\nemail: %s\nloggedIn: %s\n" % (self.name,
                                                                      self.password,
                                                                      self.email,
                                                                      self.loggedIn)
