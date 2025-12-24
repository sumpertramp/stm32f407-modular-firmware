# STM32F407 Advanced Timer (TIM1) – Complementary PWM Driver

This repository contains a **bare-metal STM32 firmware project**
focused on **advanced timer usage (TIM1)** for motor-control-ready PWM generation.

The goal of this project is not only to generate PWM,
but to build a **clean, measurable, and scalable timer infrastructure**
that can later be reused for BLDC motor control and PID-based applications.

---

## Project Goals

- Bare-metal STM32 programming (no HAL / no LL)
- Proper use of **TIM1 Advanced Timer**
- Complementary PWM generation (CH / CHN)
- Dead-time insertion for shoot-through protection
- Logic-analyzer-based verification
- Clean driver / example separation
- Motor-control-ready architecture

---

## Why TIM1 Advanced Timer?

Unlike general-purpose timers, **TIM1** is designed specifically for
motor control and power electronics.

It provides hardware features such as:

- Complementary outputs (CHx / CHxN)
- Dead-time generator
- Main Output Enable (MOE)
- Break & safety mechanisms
- Center-aligned PWM modes

These features are mandatory for:
- BLDC motors
- PMSM motors
- Half-bridge / full-bridge drivers
- ESC designs

---

## PWM Configuration

### PWM Frequency

-> PWM frequency is configured to **20 kHz**, which is commonly used in
motor control to avoid audible noise.
-> PWM Frequency = SystemCoreClock / (PSC + 1) / (ARR + 1)
-> Given:
   - SystemCoreClock = 168 MHz
   - Prescaler (PSC) = 0
   ```c
   ARR = (168,000,000 / 20,000) - 1 ≈ 8399
   ```
   -Duty cycle is controlled via the CCR register:
   ```c
   TIM1_PWM_SetDuty(1, TIM1->ARR / 2); // 50% duty
   ```

### Duty Sweep Test

A duty sweep is implemented in the example application to observe
dynamic PWM behavior using a logic analyzer.
This allows verification of duty cycle updates while ensuring
that the PWM frequency remains constant.

---

## 🔌 Pin Mapping

| Signal      | Pin  | Description                  |
|------------|------|------------------------------|
| TIM1_CH1   | PA8  | Main PWM output              |
| TIM1_CH1N  | PB13 | Complementary PWM output     |
| GND        | GND  | Common reference             |

All pins are configured in **Alternate Function mode (AF1)**.

---

## Logic Analyzer Verification

PWM signals were verified using a logic analyzer to confirm
correct advanced timer behavior.

### Logic Analyzer Capture

The following capture shows TIM1 complementary PWM outputs
measured using a logic analyzer.

![Advanced Timer Complementary PWM Logic Analyzer Capture](docs/logic_analyzer/advanced_timer_logic_analyzer_measure.png)
**Figure:** Logic analyzer capture showing TIM1_CH1 (PA8) and
TIM1_CH1N (PB13) operating in complementary PWM mode.
Dead-time between switching edges is visible, confirming
shoot-through protection.

### Dead-Time Measurement (Saleae Logic)

Dead-time was measured using manual cursors in Saleae Logic:

- Cursor A placed on TIM1_CH1 (PA8) falling edge (turn-off)
- Cursor B placed on TIM1_CH1N (PB13) rising edge (turn-on)

The time difference between the two cursors represents the configured dead-time.
![Advanced Timer Complementary PWM Dead-Time Logic Analyzer Capture](docs/logic_analyzer/advanced_timer_deadtime_logic_analyzer.pwm)
**Measured dead-time:** ~4.24 µs

This confirms that complementary outputs are properly interlocked and shoot-through protection is active.


### Observed Results

- TIM1_CH1 and TIM1_CH1N operate in **complementary mode**
- Outputs are never HIGH at the same time
- A short **dead-time gap** is visible between switching edges
- Duty cycle changes dynamically while PWM frequency remains constant

### Verified Configuration

This confirms correct configuration of:

- Advanced timer output compare mode
- Complementary output enable
- Dead-time insertion
- Main Output Enable (MOE)

> No motor or gate driver was connected.  
> All tests were performed safely at logic-level signals.

---

##  Project Structure

```text
stm32f407-modular-firmware/
│
├── drivers/
│   └── advanced_timer(pwm)/
│       ├── advanced_pwm.c
│       ├── advanced_pwm.h
│       └── advanced_pwm_regs.h
│
├── examples/
│   └── advanced_timer.c
│      
│
└── README.md
```

##  Driver Design Philosophy

- Hardware-specific register definitions are isolated from application logic
- Public API is clean, minimal, and purpose-driven
- No application-level logic exists inside the driver layer
- Designed to be reused by higher-level motor control modules

This design approach allows the same TIM1 PWM infrastructure
to be reused without modification across different applications.

---

##  Future Extensions

Planned next steps include:

- BLDC 6-step commutation
- PID-based speed control
- Gate driver integration
- Break input and over-current protection
- Hall sensor or encoder feedback

All future motor control modules will reuse
this TIM1 PWM driver as the base layer.

---

## Summary

This project demonstrates a **motor-control-ready PWM infrastructure**
using the STM32 TIM1 Advanced Timer with:

- Bare-metal implementation
- Complementary PWM outputs
- Dead-time insertion
- Measurement-based verification
- Safety-aware test methodology

The focus is on correctness, clarity, and scalability.

