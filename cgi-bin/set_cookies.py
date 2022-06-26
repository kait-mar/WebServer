#!/usr/bin/python

print ("Set-Cookie:Password = Endun;\n")
print ("Set-Cookie:UserID = Labhairi;\n")
print ("Set-Cookie:Expires = Tuesday, 31-Dec-2022 23:12:40 GMT;\n")
print ("Set-Cookie:Domain = www.1337_server.com;\n")
print ("Set-Cookie:Path = /perl;\n")

print ("""\
Content-Type: text/html\n
<html>
<body>
   <p>Cookies sent</p>
</body>
</html>
""" )
