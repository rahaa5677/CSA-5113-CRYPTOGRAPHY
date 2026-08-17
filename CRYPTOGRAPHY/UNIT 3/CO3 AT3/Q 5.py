import random

def elgamal_setup():
    # Public parameters p (prime) and g (generator)
    p = 2357
    g = 2
    x = random.randint(1, p - 2)  # Private Key
    y = pow(g, x, p)               # Public Key
    return (p, g, y), x

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    return pow(a, -1, m)

def elgamal_sign(params, private_key, message_hash):
    p, g, y = params
    x = private_key
    
    while True:
        k = random.randint(1, p - 2)
        if gcd(k, p - 1) == 1:
            break
            
    r = pow(g, k, p)
    k_inv = mod_inverse(k, p - 1)
    s = (k_inv * (message_hash - x * r)) % (p - 1)
    return (r, s)

def elgamal_verify(params, public_key_y, message_hash, signature):
    p, g, y = params
    r, s = signature
    
    if not (0 < r < p and 0 < s < p - 1):
        return False
        
    v1 = (pow(y, r, p) * pow(r, s, p)) % p
    v2 = pow(g, message_hash, p)
    return v1 == v2

# Run Simulation
params, private_key = elgamal_setup()
p, g, public_key_y = params

m_hash = 1450  # Pre-computed message hash integer
signature = elgamal_sign(params, private_key, m_hash)
is_valid = elgamal_verify(params, public_key_y, m_hash, signature)

print(f"Public Parameters (p, g, y): {params}")
print(f"Generated Signature (r, s):  {signature}")
print(f"Signature Verification:      {is_valid}")
