# SysTick Timer (STM32F407)

## Overview

This example demonstrates how to analyze **SysTick jitter** on an STM32F407
microcontroller using a **logic analyzer**.  
The goal is not only to verify that SysTick works, but to evaluate **timing
determinism** and **interrupt stability**, which are critical for real-time
embedded systems.

---

## Project Path
This example follows a modular firmware architecture.  
Only the files directly related to the SysTick timer driver and its example
are shown below.

```text
Core/
├── Src/
│   └── drivers/
│       └── systick_timer/
│           ├── systick_timer.c
│           └── systick_timer.h
│
└── examples/
    └── systick_timer/
        ├── systick_timer_example.c
        └── systick_timer_readme.md

```

## What is SysTick?

SysTick is a **24-bit down-counting timer** integrated into the ARM Cortex-M core.
It is commonly used as:

- A system time base (1 ms tick)
- A scheduler heartbeat
- The default RTOS tick source

SysTick generates an interrupt when the counter reaches zero and reloads
automatically.

---

## What is Jitter?

**Jitter** is the variation in timing between consecutive periodic events.

In the context of SysTick, jitter answers the question:

> “Does the SysTick interrupt occur at exactly the same time interval every cycle?”

Even if the *average period* is correct (e.g. 1 ms), individual ticks may arrive
slightly earlier or later due to system effects.

---

## Why SysTick Jitter Matters

Low SysTick jitter is essential for:

- Deterministic task scheduling
- Stable RTOS behavior
- Accurate software timers
- Control systems and motor control loops

High jitter may indicate:

- Long or blocking interrupt service routines
- Interrupt priority misconfiguration
- Heavy interrupt load
- Flash wait states or cache effects

---

## Typical Sources of SysTick Jitter

- Higher-priority interrupts preempting SysTick
- Long ISR execution times
- Disabled interrupts (critical sections)
- Debug interface overhead (SWD, breakpoints)
- Clock and bus latency

---

## Measurement Methodology

To measure SysTick jitter, the following approach was used:

1. A GPIO pin is toggled **directly inside the SysTick interrupt handler**
2. This ensures the signal transition occurs at the exact interrupt execution time
3. A logic analyzer captures the GPIO waveform
4. Edge-to-edge timing is analyzed to evaluate period variation

This method measures **interrupt-to-interrupt timing**, not application-level delay.

---

## Why GPIO Toggling Inside the ISR?

- Eliminates application code influence
- Avoids software delays or polling artifacts
- Measures true interrupt latency and consistency
- Common professional technique for real-time analysis

---

## Measurement Results Summary

SysTick timing accuracy and jitter were verified using a logic analyzer by
toggling a GPIO pin directly inside the SysTick interrupt handler.

### Logic Analyzer Captures

**Single-period verification (1 ms tick):**

![SysTick single period measurement](../docs/systic_timer_logic_anaylzer.PNG)

- Measured ΔT ≈ **997 µs**
- Confirms correct **~1 ms SysTick interrupt period**

**Multi-period jitter analysis:**

![SysTick jitter measurement](../docs/systick_timer_jitter_logic_analyzer.PNG)

- Mean frequency (f_mean): **~502.1 Hz**
- Minimum frequency (f_min): **~501.8 Hz**
- Maximum frequency (f_max): **~502.3 Hz**
- Period standard deviation (T_std): **~0.6 µs**

Since the GPIO is toggled on every SysTick interrupt, the expected signal
frequency is ~500 Hz (full period ≈ 2 ms), which matches the measurements.

The sub-microsecond standard deviation indicates **very low SysTick jitter**
and deterministic interrupt behavior.

---

## Interpretation of Results

A jitter standard deviation of approximately **0.5 µs** indicates:

- Very low timing variation
- Clean interrupt structure
- Short and deterministic ISR execution
- Proper interrupt priority configuration

For STM32 Cortex-M systems:

- < 1 µs jitter: Excellent
- 1–5 µs jitter: Acceptable
- > 10 µs jitter: Potential design issue

This implementation falls into the **excellent** category.

---

## Key Takeaways

- SysTick is suitable for real-time time base generation
- Measuring only functionality is insufficient; timing quality matters
- Logic analyzer–based jitter measurement provides objective proof
- Low jitter confirms deterministic interrupt behavior

---

