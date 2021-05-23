En caso de que suceda un error en el header clasesArboles.h dentro de la carpeta headers, hay que descomentar el código comentado en la parte superior del header clases, consiste en una librería y en una función, es un error que se puede presentar según el compilador al no encontrar la función to_string.

A la hora de añadir los archivos, se añade la carpeta al mismo nivel del archivo principal (Proyecto2.cpp), es decir, en la misma carpeta en la que se encuentra el archivo principal.

Por favor no retirar la carpeta headers de la misma carpeta en dónde se encuentra el archivo principal (Proyecto2.cpp), ya que ahí se encuentra toda la programación del proyecto, no modificar nada de los archivos, salvo el código comentado en la parte superior del header clasesArboles, sólo si da error con las funciones to_string en este propio header o el contenido de las funciones del header colores si diera errores.

En las opciones en que aparecen una confirmación y un: (S/N). Hay que ingresar un S, que significaría Si; o un N, que significaría No. Caulquier opción diferente de S será tomada como No.

Si por problemas con el sistema operativo u otras situaciones llegara a presentarse un error en las funciones que tienen el nombre de un color, bastaría con entrar al header de colores, eliminar el: #include <windows.h> y quitar o vaciar el contenido de las funciones que tienen por nombre un color.