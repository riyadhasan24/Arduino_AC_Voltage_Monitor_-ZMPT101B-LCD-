# Arduino AC Voltage Monitor (ZMPT101B + LCD)

This project reads real-time AC mains voltage using the **ZMPT101B sensor** and displays it on a **16x2 I2C LCD**. A relay is controlled based on voltage range, and a button allows easy calibration.

### Features
- ZMPT101B voltage sensor
- 16/02 LCD display With I2C
- Relay control (ON between 210V–230V)
- Calibration button (press when input is 220V)

### Pins
- Voltage sensor → A0  
- Relay → D13  
- LCD → I2C (A4/A5)  
- Button → D2 (INPUT_PULLUP)

### How to Calibrate
Press the button when AC input is exactly **220V**. The system will auto-adjust the voltage scaling.

---

### 📩 Contact

For help, suggestions, or collaboration, feel free to reach out:

- **📧 Email: rh30288553@gmail.com 
- **📱 WhatsApp:** +88 01730 288553
