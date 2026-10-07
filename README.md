# SISTEMA-DE-MONITOREO-OCUPACIONAL-DE-ESPACIOS-
# 📊 Sistema Automatizado de Control de Aforo con Arduino

Este proyecto consiste en un **Sistema de Monitoreo y Control de Aforo en Tiempo Real** diseñado y simulado en Tinkercad. El sistema utiliza sensores de proximidad ultrasónicos y un botón manual para contabilizar el flujo de personas en un salón, gestionando alertas visuales y sonoras según el estado de ocupación.

## 🚀 Características principales
* **Monitoreo bidireccional:** Cuenta de forma independiente las personas que entran y salen utilizando dos sensores ultrasónicos.
* **Registro de respaldo:** Incluye un botón físico para el registro manual de usuarios.
* **Bloqueo por capacidad máxima:** El sistema rechaza automáticamente nuevos ingresos cuando se alcanza el límite establecido (15 personas).
* **Indicadores de estado:** Alertas visuales mediante LEDs (Verde, Amarillo, Rojo) y sonora mediante un Buzzer activo.
* **Optimización de lectura:** Código de alto rendimiento con tiempos de espera (*timeout*) reducidos para evitar duplicaciones o lecturas falsas al cruzar.

---

## 🛠️ Componentes Utilizados
* 1x **Arduino Uno R3**
* 2x **Sensores Ultrasónicos HC-SR04** (Entrada y Salida)
* 1x **Pulsador/Botón** (Ingreso manual)
* 3x **Diodos LED** (Verde, Amarillo y Rojo)
* 1x **Buzzer/Zumbador** piezoeléctrico
* 3x Resistencias (para los LEDs y la configuración del botón)
* 1x Protoboard y cables de conexión


## 🚥 Lógica de Ocupación (Capacidad Máxima: 15)
El sistema evalúa constantemente la cantidad de personas dentro del salón y reacciona de la siguiente manera:

| Cantidad de Personas | Estado del Salón | Indicador Activo |
| :--- | :--- | :--- |
| `0` | Vacío | Ninguno |
| `1 a 5` | Ocupación Baja | 🟢 LED Verde ENCENDIDO |
| `6 a 14` | Ocupación Media / Alta | 🟡 LED Amarillo ENCENDIDO |
| `15` | **Capacidad Máxima Alcanzada** | 🔴 LED Rojo ENCENDIDO + 🔊 Alerta de Buzzer |

---

## 🔌 Conexiones de Pines (Arduino Uno)

### Entradas (Sensores y Botones)
* **Sensor Entrada:** `Trig` -> Pin 12 | `Echo` -> Pin 11
* **Sensor Salida:** `Trig` -> Pin 10 | `Echo` -> Pin 9
* **Botón Manual:** Pin 8

### Salidas (Actuadores)
* **LED Verde:** Pin 7
* **LED Amarillo:** Pin 6
* **LED Rojo:** Pin 4
* **Buzzer:** Pin 5

---

## 💻 Simulación en Tinkercad
Puedes ver e interactuar con el diseño electrónico original de este proyecto a través del siguiente enlace:

🔗 [Ver Proyecto en Tinkercad](https://www.tinkercad.com/things/8tBAN1GXdK9-sistema-de-monitoreo-ocupacional-de-espacios-sara-ruiz-j/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=r4z9YqKjXZGZAgeJYZi_DOnfgI7RWC0wnxkecgSR-Q4)
