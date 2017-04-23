Para generar el ejecutable (en el mismo directorio): make main
Esto creará los archivos .o de las librerías correspondientes y compilará el main

El main se explica bastante por si mismo.
	1. Con el primer parámetro se decide si usar claves aleatorias o passwords
	2. Con el segundo parámetro se decide el numero de claves (y la longitud en el caso de claves aleatorias)
	3. Se decide si crear el bloom filter a partir del error o del tamaño
	4. Si usar alguna función criptográfica para la entrada

Si no ha habido ningún error, saldrá información sobre el bloom filter creado y los errores en los alrededor de 7 millones de queries hechas en él.
	