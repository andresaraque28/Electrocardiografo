import matplotlib.animation as animation
import matplotlib.pyplot as plt
import serial

datos = [] 
max_datos = 500

fig, ax = plt.subplots()
line, = ax.plot([], [])

def inicializar():
    ax.set_xlim(0, max_datos)
    ax.set_ylim(0, 2)  # Ajusta el rango del eje y a tus necesidades de voltaje
    ax.set_title('Señal ECG')
    ax.set_xlabel('Muestras')
    ax.set_ylabel('Voltaje (V)')
    return line,

def graficar(i):
    global datos
    ax.set_title('Datos desde Arduino')
    ax.set_xlabel('Muestras')
    ax.set_ylabel('Voltaje (V)')
    valor = int(ser.readline())
    voltaje = (valor / 1023) * 5  # Conversión a voltios
    datos.append(voltaje)
    datos = datos[-max_datos:]
    line.set_data(range(len(datos)), datos)
    return line,

ani = animation.FuncAnimation(fig, graficar, init_func=inicializar, interval=50, blit=True)

try:
    ser = serial.Serial('COM5', 9600)
    plt.show()
finally:
    if ser.is_open:
        ser.close()



        
