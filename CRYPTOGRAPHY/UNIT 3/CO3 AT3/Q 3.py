import hashlib

def simple_hash_check(secret_key, message):
    # Naive prefix construction: Hash(key || message) - vulnerable to length extension attacks
    return hashlib.sha256(secret_key + message).hexdigest()

def hmac_sha256(key, message):
    block_size = 64  # Block size for SHA-256
    
    if len(key) > block_size:
        key = hashlib.sha256(key).digest()
    if len(key) < block_size:
        key = key.ljust(block_size, b'\x00')
        
    o_key_pad = bytes([b ^ 0x5c for b in key])
    i_key_pad = bytes([b ^ 0x36 for b in key])
    
    inner_hash = hashlib.sha256(i_key_pad + message).digest()
    return hashlib.sha256(o_key_pad + inner_hash).hexdigest()

key = b"supersecretkey"
msg = b"Transaction Payload Data"

simple_tag = simple_hash_check(key, msg)
hmac_tag = hmac_sha256(key, msg)

print(f"Simple Hash Tag: {simple_tag}")
print(f"HMAC Tag:        {hmac_tag}")
