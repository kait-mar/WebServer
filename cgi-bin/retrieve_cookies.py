#!/usr/bin/python



import os

# Hello world python program
print ("Content-Type: text/html\n")

handler = {}
if 'HTTP_COOKIE' in os.environ:
    cookies = os.environ['HTTP_COOKIE']
    cookies = cookies.split('; ')

    for cookie in cookies:
        cookie = cookie.split('=')
        handler[cookie[0]] = cookie[1]

for k in handler:
    print (k + " = " + handler[k])
