import time

class KerberosAS:
    def __init__(self, client_id, client_key, tgs_key):
        self.client_id = client_id
        self.client_key = client_key
        self.tgs_key = tgs_key

    def get_tgt(self, requested_id):
        if requested_id != self.client_id:
            return None, "Authentication Failed"
        timestamp = time.time()
        # Ticket Granting Ticket structure: (Client_ID, Timestamp, Lifetime)
        tgt = {"client_id": self.client_id, "timestamp": timestamp, "ttl": 5}
        return tgt, "TGT Issued Successfully"

class KerberosServer:
    def __init__(self, lifetime=5):
        self.lifetime = lifetime

    def validate_ticket(self, tgt, client_id):
        current_time = time.time()
        
        # Check Identity
        if tgt["client_id"] != client_id:
            return False, "Access Denied: Invalid Identity"
            
        # Replay Attack Prevention Check via Timestamp
        if current_time - tgt["timestamp"] > tgt["ttl"]:
            return False, "Access Denied: Ticket Expired (Replay Detected)"
            
        return True, "Access Granted"

# Simulation
as_server = KerberosAS(client_id="user_alice", client_key="password123", tgs_key="tgs_secret")
app_server = KerberosServer()

# 1. Authentic request
tgt, msg = as_server.get_tgt("user_alice")
valid, status = app_server.validate_ticket(tgt, "user_alice")
print(f"Immediate Validation: {status}")

# 2. Replay attack attempt after expiration delay
time.sleep(6)
replay_valid, replay_status = app_server.validate_ticket(tgt, "user_alice")
print(f"Replay Validation (After 6s): {replay_status}")
