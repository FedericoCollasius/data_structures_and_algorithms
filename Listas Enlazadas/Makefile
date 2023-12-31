NOMBRE_ZIP=taller_lista_enlazada

all: clean taller_lista_enlazada.zip

clean:
	rm -f ${NOMBRE_ZIP}.zip

${NOMBRE_ZIP}.zip: enunciado/${NOMBRE_ZIP}.pdf
	mv alumnos ${NOMBRE_ZIP}
	cp enunciado/${NOMBRE_ZIP}.pdf ${NOMBRE_ZIP}/enunciado.pdf
	zip -r $@ \
		${NOMBRE_ZIP}/src/*.h \
		${NOMBRE_ZIP}/src/*.hpp \
		${NOMBRE_ZIP}/src/*.cpp \
		${NOMBRE_ZIP}/tests/ \
		${NOMBRE_ZIP}/CMakeLists.txt \
		${NOMBRE_ZIP}/enunciado.pdf \
		${NOMBRE_ZIP}/tests/gtest-1.8.1/*.cc \
		${NOMBRE_ZIP}/tests/gtest-1.8.1/*.h	\
		${NOMBRE_ZIP}/tests/gtest-1.8.1/*.hpp \
		${NOMBRE_ZIP}/tests/gtest-1.8.1/*.cpp	
	rm ${NOMBRE_ZIP}/enunciado.pdf
	mv ${NOMBRE_ZIP} alumnos

enunciado/${NOMBRE_ZIP}.pdf:
	make -C enunciado
