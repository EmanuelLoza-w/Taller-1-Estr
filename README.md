Emanuel Loza Q. 
Paralelo C2
Codigo creado en Clion, funcional hasta el momento de subir el taller, ante un posible error:
ld.exe: cannot open output file ejemplo.exe: Permission denied
Puede ser que el codigo sigue abierto y ejecutandose en algún lado(me pasó).
Para resolverlo usé en la cmd del build:  
tasklist | findstr /I prototipo.exe           
taskkill /IM prototipo.exe /F        
Ante cualquier otro error saquenme del ramo :)
