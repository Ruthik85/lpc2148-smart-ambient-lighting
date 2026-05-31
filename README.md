# lpc2148-smart-ambient-lighting
An ARM7 (LPC21xx) automated ambient lighting system designed in C. Integrates RTC for time windows, ADC for LDR light-intensity parsing, hardware interrupts (EINT0), a matrix keypad, and an LCD interface. Dynamically manages power consumption based on environmental lux and real-time schedules.
# ARM7 (LPC21xx) Automated Smart Ambient Lighting System

An advanced, energy-efficient embedded application implementing an automated **Smart Ambient Lighting Controller** using an ARM7-TDMI LPC21xx microcontroller. Developed in embedded C, this system synchronizes an on-chip Real-Time Clock (RTC) with an Analog-to-Digital Converter (ADC) to drive ambient light arrays dynamically based on schedule parameters and environmental lighting levels.

---

## 🚀 Project Architecture & Features

The system intelligently monitors time-of-day windows and physical lighting variations to maximize energy efficiency while keeping manual calibration controls highly accessible.

### Core System Workflow
1. **Time-Window Restriction:** The main control loop checks the RTC. Sensor-driven ambient lighting is only permitted during night profiles (**18:00 to 06:00**).
2. **Dynamic LDR Threshold Tuning:** During active night intervals, the internal 10-bit successive-approximation ADC tracks an external LDR sensor circuit. If ambient light falls below a calibrated limit (`ldrv < 200`), the controller triggers GPIO pins to activate the high-efficiency LED arrays.
3. **Asynchronous Interrupt Routine:** Pressing a hardware button triggers an External Interrupt (**EINT0**). This immediately halts the primary loop to launch a safe, menu-driven UI context for runtime calibration.
4. **Interactive Hardware Calibration UI:** Users can dynamically adjust system time, date, and calendar variables at any point using a 4x4 Matrix Keypad and a character LCD panel.

---

## 🛠️ Hardware & Software Ecosystem

* **Microcontroller Core:** NXP LPC2148 / LPC2124 (ARM7-TDMI-S)
* **Development Environment:** Keil uVision IDE
* **Compiler Target:** ARM-Thumb Compiler (CARM / AC5)
* **Simulation & Layout Platform:** Proteus Design Suite
* **Integrated Peripherals:**
  * **Internal RTC:** Dedicated 32.768 kHz oscillator tracking time/date configurations.
  * **Internal ADC:** 10-bit analog conversion capturing LDR voltage drops.
  * **VIC (Vectored Interrupt Controller):** Configured for Vectored IRQ slot allocations handling EINT0.
  * **User I/O Components:** 16x2 Character LCD, 4x4 Keypad Matrix, Serial UART0 Terminal, and GPIO-driven LED/relay modules.

---

## ⚙️ Pin Out Configuration Map

| Hardware Component | Microcontroller Pin | Function Mode | Pin Description |
| :--- | :--- | :--- | :--- |
| **LED / Actuator** | P1.28 | GPIO Output | Controls Ambient Light Driver |
| **LDR Sensor Input** | P0.28 (AD0.1) | AD0.1 / Function 1 | ADC Channel 1 Voltage Capture |
| **Interrupt Button** | P0.16 (EINT0) | EINT0 / Function 2 | Asynchronous ISR Context Switch |
| **UART0 Tx/Rx** | P0.0 / P0.1 | TXD0 / RXD0 | Serial System Telemetry Log |
| **Keypad / LCD** | Port 0 / Port 1 | GPIO Custom Blocks | Human-Machine UI Bus |

---

## 📁 Repository Structure

```text
├── src/                          # Firmware Codebase
│   ├── main.c                    # State engine and primary control loops
│   ├── eint0_isr.c               # Vectored Interrupt Service Routines
│   ├── config/                   # Low-level driver configurations
│   │   ├── adc.h / rtc.h         # Peripheral Register Abstractions
│   │   ├── lcd.h / kpm.h         # Interface Bus Header Declarations
│   │   └── delay.h               # Hardware-timer tick operations
├── simulation/                   # Layout Verification
│   └── ambient_lighting_sim.dsn  # Proteus structural schematic
└── README.md                     # Technical Documentation
