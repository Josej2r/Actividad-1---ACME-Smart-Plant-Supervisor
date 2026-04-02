# 🏭 ACME S.A. - Smart Plant Supervisor Node

Este repositorio contiene el firmware y la configuración de hardware para el nodo de supervisión IoT desarrollado para la planta de producción de motores de tracción de ACME S.A.

## 📋 Descripción del Proyecto
El sistema implementa una solución de clasificación automática y monitorización ambiental en tiempo real. Utiliza un microcontrolador para diferenciar cajas de motores (Ascensor vs. Escalera Mecánica) mediante ultrasonidos, al mismo tiempo que registra las variables críticas del entorno (temperatura, humedad e iluminación) para proteger los componentes electrónicos.

## 🛠️ Tecnologías y Hardware Utilizado
* **Entorno de Desarrollo:** PlatformIO (Visual Studio Code)
* **Lenguaje:** C++ (Framework Arduino)
* **Placa Base:** Arduino Mega 2560
* **Sensores:**
  * HC-SR04 (Sensor Ultrasónico de Distancia)
  * DHT22 (Sensor de Temperatura y Humedad)
  * LDR (Fotorresistencia para monitorización lumínica)
* **Interfaz (HMI):** Pantalla LCD 20x4 con módulo I2C

## ⚙️ Características Principales
1. **Clasificación Geométrica:** Detección y conteo de piezas según su altura utilizando ecos ultrasónicos.
2. **Seguridad Industrial:** Monitoreo constante del clima con tolerancia a fallos.
3. **Telemetría SCADA:** Registro continuo por puerto serie con un formato estructurado de datos.
4. **HMI Local:** Interfaz ergonómica que muestra el estado de la línea de producción y alarmas en tiempo real.

## 🚀 Simulación y Pruebas
El esquema de conexiones ha sido diseñado utilizando la plataforma **Wokwi**.

* **Esquema de conexiones (Wokwi):** [Enlace](https://wokwi.com/projects/460109066564689921)


<img width="662" height="536" alt="image" src="https://github.com/user-attachments/assets/38dd376f-7c15-4beb-8c14-3a12bbcde394" />

---
*Desarrollado como actividad para la asignatura Equipos e Instrumentación Electrónica.*
