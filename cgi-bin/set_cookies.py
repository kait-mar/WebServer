#!/usr/bin/python

print ("Set-Cookie:Password = casanegra;\n")
print ("Set-Cookie:UserID = XYZ;\n")
print ("Set-Cookie:Expires = Tuesday, 31-Dec-2007 23:12:40 GMT;\n")
print ("Set-Cookie:Domain = www.tutorialspoint.com;\n")
print ("Set-Cookie:Path = /perl;\n")
print ("Set-Cookie:Mouuad = Labhairi\n")

print ("""\
Content-Type: text/html\n
<html>
<body>
   <p>Cookies sent</p>
</body>
</html>
""" )
