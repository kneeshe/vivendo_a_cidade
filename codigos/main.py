from flask import Flask, request, jsonify

app = Flask(__name__)

estado_onibus = {
    "onibus1": False,
    "onibus2": False,
    "onibus3": False,
    "onibus4": False
}

@app.route("/solicitar/<onibus_id>", methods=["POST"])
def solicitar_parada(onibus_id):
    if onibus_id in estado_onibus:
        estado_onibus[onibus_id] = True
        return jsonify({"status": "solicitado"})
    return jsonify({"erro": "ônibus não encontrado"}), 404

@app.route("/chegou/<onibus_id>", methods=["GET"])
def verificar_chegada(onibus_id):
    if onibus_id in estado_onibus:
        status = estado_onibus[onibus_id]
        return jsonify({"chegou": status})
    return jsonify({"erro": "ônibus não encontrado"}), 404

@app.route("/resetar/<onibus_id>", methods=["POST"])
def resetar_onibus(onibus_id):
    if onibus_id in estado_onibus:
        estado_onibus[onibus_id] = False
        return jsonify({"status": "resetado"})
    return jsonify({"erro": "ônibus não encontrado"}), 404

app.run(host="0.0.0.0", port=5000)
