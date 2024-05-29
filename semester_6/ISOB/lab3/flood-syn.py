import random
import time

class Packet:
    def __init__(self, src_ip, dst_ip, syn=False, ack=False):
        self.src_ip = src_ip
        self.dst_ip = dst_ip
        self.syn = syn
        self.ack = ack

class Server:

    def __init__(self, max_pending_connections, server_ip):
        self.server_ip = server_ip
        self.max_pending_connections = max_pending_connections
        self.pending_connections = {}

    def receive_packet(self, packet):
        if packet.syn and packet.src_ip not in self.pending_connections:
            if len(self.pending_connections) < self.max_pending_connections:
                self.pending_connections[packet.src_ip] = True
                print(f"Server received SYN from {packet.src_ip}. Sending SYN+ACK.")
                return Packet(src_ip=packet.dst_ip, dst_ip=packet.src_ip, syn=True, ack=True)
            else:
                print("Server reached maximum connections. Ignoring SYN request.")
                return None
        elif packet.ack and packet.src_ip in self.pending_connections:
            del self.pending_connections[packet.src_ip]
            print(f"Server received ACK from {packet.src_ip}. Connection established.")
        else:
            print("Server received unexpected packet. Ignoring.")

def generate_random_ip():
    return ".".join(str(random.randint(0, 255)) for _ in range(4))

class Client:
    def send_packet(self, server):
        src_ip = generate_random_ip()
        packet = Packet(src_ip=src_ip, dst_ip=server.server_ip, syn=True)
        print(f"[Client] Sending packet to {packet.dst_ip}, packet_sourse = {packet.src_ip}")
        server.receive_packet(packet)
        return packet



def main():
    server = Server(max_pending_connections=3, server_ip='123.123.123.123')
    client = Client()

    for i in range(5):  # Sending 5 SYN packets
        response = client.send_packet(server)


if __name__ == "__main__":
    main()
