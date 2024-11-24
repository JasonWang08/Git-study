import matplotlib.pyplot as plt
import numpy as np

# Define frequency range
omega = np.logspace(-2, 3, 1000)  # Frequency range from 0.01 to 1000

# Calculate magnitude and phase
s = 1j * omega
H = 100 * (s + 10) / (s * (s + 1) * (s + 100))

magnitude = 20 * np.log10(np.abs(H))
phase = np.angle(H, deg=True)

# Plot magnitude
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.semilogx(omega, magnitude)
plt.title('Bode Plot')
plt.ylabel('Magnitude (dB)')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# Plot phase
plt.subplot(2, 1, 2)
plt.semilogx(omega, phase)
plt.ylabel('Phase (degrees)')
plt.xlabel('Frequency (rad/s)')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

plt.show()
