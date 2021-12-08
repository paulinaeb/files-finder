# files-finder
Proyecto de Sistemas Distribuidos

Implementación de un servicio de búsqueda de archivos en múltiples máquinas (incluyendo la local), al estilo el comando find de Linux. Para lo cual se debe hace uso de los protocolos UDP y TCP, con los siguientes componentes:<br />
-Cliente UDP – Con interfaz de línea de comando <br />
-Cliente TCP – Con Interfaz de línea de comando <br />
-Servidor UDP (en el puerto 2002) <br />
-Servidor TCP <br />
*Implementado con procesos (en el puerto 2002) <br />
*Implementado con hilos (en el puerto 2020) <br />
En todos los casos los clientes se implementaron con hilos para disminuir el tiempo de búsqueda, así mismo se ofrecen opciones para cambiar el puerto del servicio por defecto y obtener ayuda del comando.
El desarrollo se desarrolló en un entorno Linux usando los API de socket y el lenguaje de programación C, y definiendo los diferentes protocolos de aplicación, tanto en UDP como en TCP.

#Para compilar el archivo principal se debe correr en la terminal las siguientes instrucciones

usando el comando completo: gcc main.c -o main -l pthread<br />

usando make: make

#luego para ejecutarlo

./main

