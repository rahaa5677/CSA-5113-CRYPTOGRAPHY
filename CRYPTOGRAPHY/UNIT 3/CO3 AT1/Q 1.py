import hashlib
import time

messages = [
    b"Hello, World!",
    b"Cryptography and Network Security",
    b"A" * 1000000  # 1 MB data block
]

print(f"{'Algorithm':<10} | {'Input Size (bytes)':<20} | {'Execution Time (s)':<20} | {'Hash (First 16 hex chars)':<25}")
print("-" * 80)

for msg in messages:
    # MD5 Performance
    start = time.perf_counter()
    md5_hash = hashlib.md5(msg).hexdigest()
    md5_time = time.perf_counter() - start
    print(f"{'MD5':<10} | {len(msg):<20} | {md5_time:<20.6f} | {md5_hash[:16]}...")

    # SHA-256 Performance
    start = time.perf_counter()
    sha256_hash = hashlib.sha256(msg).hexdigest()
    sha256_time = time.perf_counter() - start
    print(f"{'SHA-256':<10} | {len(msg):<20} | {sha256_time:<20.6f} | {sha256_hash[:16]}...")
    print("-" * 80)

# Collision Resistance Analysis Summary:
# - MD5: Cryptographically broken. Known collision attacks exist with minimal computing effort.
# - SHA-256: Current industry standard, highly resilient against collision and preimage attacks.
