import sys

def corrigir_hamming(bits):
    b = list(map(int, bits))
    p1 = b[0]
    p2 = b[1]
    d1 = b[2]
    p3 = b[3]
    d2 = b[4]
    d3 = b[5]
    d4 = b[6]

    c1 = p1 ^ d1 ^ d2 ^ d4
    c2 = p2 ^ d1 ^ d3 ^ d4
    c3 = p3 ^ d2 ^ d3 ^ d4

    erro = c1 * 1 + c2 * 2 + c3 * 4
    if erro != 0:
        print(f"Bit com erro na posição: {erro}")
        b[erro - 1] ^= 1

    return f"{b[2]}{b[4]}{b[5]}{b[6]}"

def extrair_payload(frame):
    cabecalho = "01111110"
    terminador = "01111110"

    if not (frame.startswith(cabecalho) and frame.endswith(terminador)):
        raise ValueError("Frame inválido: ausência de delimitadores")

    dados_codificados = frame[len(cabecalho):-len(terminador)]
    return corrigir_hamming(dados_codificados)

if __name__ == "__main__":
    entrada = sys.stdin.read().strip()
    payload_corrigido = extrair_payload(entrada)
    print(payload_corrigido)
