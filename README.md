# ⚡ 7×6 RGB LED Matrix — *Custom‑Built, Fully Multiplexed, and Over‑Engineered on Purpose*

Welcome to one of my favorite hardware builds so far — a **hand‑crafted 7×6 RGB LED matrix** powered by **4‑pin RGB LEDs**, **shift registers**, and **transistor arrays**.  
This isn’t your typical LED grid. It’s a deep dive into timing, current control, multiplexing, and the art of making way too many wires behave.

---

## 🚀 Highlights  
- **42 individually addressable RGB pixels**  
- **4‑pin RGB LEDs** for true color mixing  
- **4× 74HC595 shift registers** for scalable column control  
- **Transistor arrays** for row driving and current handling  
- **High‑speed multiplexing** for smooth, flicker‑free output  
- Designed for **microcontrollers**, animations, and custom patterns  

---

## 🧠 System Architecture  
A quick look at the signal flow:

┌────────────────┐
│ Microcontroller│
└───────┬────────┘
│ Serial Data
┌───────▼────────┐
│ Shift Registers│  →  Column Control (RGB channels)
└───────┬────────┘
│
┌───────▼────────┐
│ Transistor Bank│  →  Row Switching
└───────┬────────┘
│
┌───────▼──────────────┐
│ 7×6 RGB LED Matrix   │
└──────────────────────┘


---

## 🔧 Hardware Breakdown  

### Components  
| Part | Role |
|------|------|
| **4‑pin RGB LEDs** | Full‑color pixels with shared anode/cathode |
| **74HC595 shift registers** | Serial‑to‑parallel expansion |
| **ULN2803 / transistor arrays** | High‑current row drivers |
| **Resistors** | Current limiting for each color channel |
| **Custom wiring / PCB** | Routing the chaos |

---

## 🎨 How It All Works  
- The **shift registers** push out RGB data for each column.  
- The **transistor arrays** rapidly switch rows on and off.  
- The matrix is refreshed fast enough that your eyes blend the frames into a stable image.  
- PWM on each color channel enables **smooth gradients, fades, and animations**.  
- The result: a compact, bright, and surprisingly capable RGB display.

---

## 🛠️ Future Plans  
- Add a full animation engine  
- Build a custom PCB to replace the spaghetti wiring  
- Add wireless control (BLE / Wi‑Fi)  
- Experiment with gamma correction and brightness curves  

---

## 🧾 License  
MIT License — hack it, remix it, improve it.
