# files-finder
Proyecto de Sistemas Distribuidos

Se desea implementar un servicio de búsqueda de archivos en múltiples máquinas (incluyendo la local), al estilo el comando find de Linux. Para lo cual se debe hacer uso de los protocolos UDP y TCP, e implementar los siguientes componentes:
 Cliente UDP – Con interfaz de línea de comando
 Cliente TCP – Con Interfaz de línea de comando
 Servidor UDP (en el puerto 2002)
 Servidor TCP
 Implementado con procesos (en el puerto 2002)
 Implementado con hilos (en el puerto 2020)
En todos los casos los clientes se debe implementar con hilos para disminuir el tiempo de búsqueda, así mismo se recomienda ofrecer opciones para poder cambiar el puerto del servicio por defecto y obtener ayuda del comando.
El desarrollo se debe realizar en un entorno Linux para lo cual deben utilizar los API de socket y el lenguaje de programación C, así mismo deben definir los diferentes protocolos de aplicación, tanto en UDP como en TCP.
