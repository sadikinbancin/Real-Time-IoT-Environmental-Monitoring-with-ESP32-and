from flask import Flask, request, jsonify

app = Flask(__name__)

# Variabel global untuk menyimpan data terbaru
latest_data = {
    'temperature': None,
    'humidity': None,
    'air_quality': None
}

@app.route('/data', methods=['GET'])
def get_data():
    # Membuat tabel HTML untuk menampilkan data
    table_html = f"""
    <h1>Real-Time IoT Environmental Monitoring with ESP32 and Flask</h1>
    <table border="1">
      <tr>
        <th>Parameter</th>
        <th>Value</th>
      </tr>
      <tr>
        <td>Temperature</td>
        <td>{latest_data['temperature']} °C</td>
      </tr>
      <tr>
        <td>Humidity</td>
        <td>{latest_data['humidity']} %</td>
      </tr>
      <tr>
        <td>Air Quality</td>
        <td>{latest_data['air_quality']}</td>
      </tr>
    </table>
    """

    return table_html

@app.route('/data', methods=['POST'])
def post_data():
    global latest_data

    if request.is_json:
        data = request.get_json()
        temperature = data.get('temperature')
        humidity = data.get('humidity')
        air_quality = data.get('air_quality')

        # Update data terbaru
        latest_data = {
            'temperature': temperature,
            'humidity': humidity,
            'air_quality': air_quality
        }

        response = {
            'message': 'Data received',
            'temperature': temperature,
            'humidity': humidity,
            'air_quality': air_quality
        }
        return jsonify(response), 200
    else:
        return jsonify({'error': 'Invalid data format'}), 400

# Route untuk menampilkan pesan jika belum ada data yang diterima
@app.route('/', methods=['GET'])
def home():
    # Cek apakah sudah ada data yang diterima
    if all(value is None for value in latest_data.values()):
        return "<h1>Real-Time IoT Environmental Monitoring with ESP32 and Flask</h1><p>Data belum tersedia.</p>"
    else:
        return get_data()

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
