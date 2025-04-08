import sys

def aplicar_codigo_hamming(bits):
    m = list(map(int, bits))
    if len(m) != 4:
        raise ValueError("Payload must have only 4 bits")

    p1 = m[0] ^ m[1] ^ m[3]
    p2 = m[0] ^ m[2] ^ m[3]
    p3 = m[1] ^ m[2] ^ m[3]
    return f"{p1}{p2}{m[0]}{p3}{m[1]}{m[2]}{m[3]}"

def construir_frame(payload_bin):
    cabecalho = "01111110"
    terminador = "01111110"
    payload_codificado = aplicar_codigo_hamming(payload_bin)
    return cabecalho + payload_codificado + terminador

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python remetente.py <mensagem binária de 4 bits>")
        sys.exit(1)
    mensagem = sys.argv[1]
    frame = construir_frame(mensagem)
    print(frame)
