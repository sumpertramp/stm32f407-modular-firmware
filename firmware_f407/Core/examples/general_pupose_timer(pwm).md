# STM32 General Purpose Timer – PWM (TIM4)

This project demonstrates **hardware PWM generation** using a
**General Purpose Timer (TIM4)** on **STM32F407 Discovery** in
**bare-metal (no HAL, no CubeMX)** mode.

The onboard **yellow LED (PD13)** is driven via **TIM4_CH2**,
allowing the LED brightness to **smoothly increase and decrease**
using PWM duty cycle modulation.

This module is designed as a **foundation for LED dimming,
DC motor speed control, and PID-based control systems**.
---
## Timer Types in STM32

STM32 microcontrollers provide different timer types,
each designed for specific use cases.

| Timer Type | Examples | Capabilities |
|-----------|---------|--------------|
| Basic Timers | TIM6, TIM7 | Time base, interrupts only |
| General Purpose Timers | TIM2–TIM5 | PWM, Input Capture, Output Compare, Encoder |
| Advanced Timers | TIM1, TIM8 | Complementary PWM, dead-time, motor control |

In this project, **TIM4** is used as a **General Purpose Timer**
to generate hardware PWM signals.
---
## Hardware Mapping (STM32F407 Discovery)

The STM32F407 Discovery board connects its onboard LEDs
directly to **TIM4 channels**.

| LED Color | GPIO Pin | Timer | Channel | Alternate Function |
|---------|---------|-------|---------|--------------------|
| Yellow | PD13 | TIM4 | CH2 | AF2 |
---
⚠️ **Important:**  
PWM output requires:
- Timer channel support
- GPIO configured as **Alternate Function**
- Correct AF selection

Using GPIO output mode will **not** produce PWM.
---
## What Is PWM?

**PWM (Pulse Width Modulation)** is a technique that allows
analog-like control using a digital signal.

- The signal frequency remains constant
- The **ON time** of the signal changes

This makes PWM ideal for:
- LED brightness control
- DC motor speed control
- Power regulation
---
## Duty Cycle

Duty cycle represents the percentage of time
the signal remains ON during one PWM period.

Duty Cycle (%) formula:

Duty = (ON Time / Period) × 100

| Duty Cycle | Effect |
|-----------|-------|
| 0% | Output OFF |
| 50% | Half brightness / medium speed |
| 100% | Fully ON |
---
## PWM Frequency Calculation

PWM frequency is determined by the timer clock,
prescaler (PSC), and auto-reload register (ARR).

PWM Frequency formula:

PWM_Freq = Timer_Clock / ((PSC + 1) × (ARR + 1))
---
## Frequency Configuration Used in This Project

- APB1 Timer Clock: 84 MHz
- Prescaler (PSC): 83

Timer tick frequency:

84 MHz / (83 + 1) = 1 MHz

Target PWM frequency: 1 kHz

ARR calculation:

ARR = (1,000,000 / 1,000) - 1 = 999

This provides:
- 1 kHz PWM frequency
- 1000 discrete duty steps
---
## Why Preload Is Used

Preload registers ensure that PWM updates occur
only at the end of the current PWM period.

Benefits:
- Prevents signal glitches
- Provides stable LED brightness
- Essential for motor control applications

Registers involved:
- OCxPE (Output Compare Preload Enable)
- ARPE (Auto-Reload Preload Enable)
---
## Runtime Behavior

1. TIM4 is configured in PWM mode
2. PD13 is mapped to TIM4_CH2 using AF2
3. Duty cycle increases gradually from 0% to 100%
4. Duty cycle decreases gradually from 100% to 0%
5. LED brightness smoothly fades in and out
---
## Project Structure
'''text
Drivers/
└── timer_pwm/
    ├── timer_pwm.c
    └── timer_pwm.h

Core/
├── Src/
│   └── main.c
└── examples/
    └── general_purpose_timer_pwm.c
'''
---
## Extending This Module

This PWM infrastructure can be reused for:

- LED dimming systems
- DC motor speed control
- MOSFET or H-bridge drivers
- Encoder + PID closed-loop control
- Motor control applications

The driver logic remains unchanged when
switching from LED control to motor control.
---
## Key Takeaway

PWM requires **all three** components:

1. Timer
2. Channel
3. Alternate Function GPIO

If any of these are missing,
PWM will not reach the output pin.
