import hashlib
import random

def is_prime(n):
    if n < 2: return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0: return False
    return True

def generate_keypair():
    # Simple small prime generation for demonstration purposes
    primes = [i for i in range(100, 300) if is_prime(i)]
    p, q = random.sample(primes, 2)
    n = p * q
    phi = (p - 1) * (q - 1)
    
    e = 65537
    while gcd(e, phi) != 1:
        e = random.randrange(3, phi, 2)
        
    d = pow(e, -1, phi)
    return ((e, n), (d, n))

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def sign_message(message, private_key):
    d, n = private_key
    # Hash the message first (Hash-then-Sign)
    msg_hash = int(hashlib.sha256(message.encode()).hexdigest(), 16)
    signature = pow(msg_hash, d, n)
    return signature

def verify_signature(message, signature, public_key):
    e, n = public_key
    msg_hash = int(hashlib.sha256(message.encode()).hexdigest(), 16)
    decrypted_hash = pow(signature, e, n)
    return (msg_hash % n) == decrypted_hash

# Demonstration
pub_key, priv_key = generate_keypair()
msg = "Transfer $5000 to Account X"

sig = sign_message(msg, priv_key)
is_valid = verify_signature(msg, sig, pub_key)
is_tampered_valid = verify_signature("Transfer $50000 to Account X", sig, pub_key)

print(f"Original Message: {msg}")
print(f"Signature: {sig}")
print(f"Verification Result (Original): {is_valid}")
print(f"Verification Result (Tampered): {is_tampered_valid}")
