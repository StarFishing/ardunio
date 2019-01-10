# codinf:utf-8
from flask import Flask, render_template, Response, request
import serial
port = "/dev/ttyACM0"
app = Flask(__name__)
single = serial.Serial(port, 9600)
single.flushInput()


@app.route('/')
def index():
    single.flushOutput()
    single.flushInput()
    single.write('8')
    response = str(single.readline().decode())
    if response.startswith('hum:'):
        # cut int num
        hum = response[5:7]
        tem = response[-6:-3]
        templateData = {
            'tem': tem,
            'hum': hum
        }
        print(response.strip('\n'))
        return render_template('index.html', **templateData)


@app.route('/fopen', methods=['POST', 'GET'])
def fopen():
    if request.method == 'GET':
        return render_template('index.html')
    else:
        single.flushOutput()
        single.write('1')
        return "Open OK"


@app.route('/fclose', methods=['POST'])
def fclose():
    single.flushOutput()
    single.write('2')
    return "Close OK"


@app.route('/lclose', methods=['POST'])
def lclose():
    # single.flushOutput()
    # single.write('3')
    return "LED Close OK"


@app.route('/lopen', methods=['POST'])
def lopen():
    # single.flushOutput()
    # single.write('4')
    return "LED Open OK"


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True, threaded=True)
