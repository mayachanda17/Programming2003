import matplotlib.pyplot as plt
import numpy as np

# example momentum bins (GeV/c)
p_bins = np.array([0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0])

# mean asymmetry and sub-sample uncertainties per bin
asym_pi = np.array([0.005, -0.002, 0.008, 0.001, -0.004, 0.003, 0.002, -0.001])
err_pi  = np.array([0.012,  0.015, 0.018, 0.021,  0.025, 0.028, 0.032,  0.038])

asym_p  = np.array([0.045,  0.052, 0.038, 0.021,  0.010, 0.005, 0.000, -0.008])
err_p   = np.array([0.035,  0.038, 0.042, 0.048,  0.055, 0.062, 0.070,  0.082])

plt.figure(figsize=(9, 5))
plt.axhline(0, color='gray', linestyle='--', linewidth=1)

plt.errorbar(p_bins, asym_pi, yerr=err_pi, fmt='o-', capsize=4, label=r'$\pi^+ / \pi^-$ asymmetry', color='blue')
plt.errorbar(p_bins, asym_p, yerr=err_p, fmt='s-', capsize=4, label=r'$p / \bar{p}$ asymmetry', color='red')

plt.xlabel(r'Momentum $P$ (GeV/$c$)', fontsize=12)
plt.ylabel(r'Asymmetry $A(P) = \frac{N_+ - N_-}{N_+ + N_-}$', fontsize=12)
plt.title('Particle-Antiparticle Asymmetry as a Function of Momentum', fontsize=13)
plt.ylim(-0.15, 0.15)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(fontsize=11)
plt.tight_layout()

# save plot image locally in repository directory
plt.savefig('asymmetry_vs_momentum.png', dpi=300)
