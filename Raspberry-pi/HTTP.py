import requests
import json

url = "http://10.2.16.116:8610/cin/create/19"
data = {
  "BinData": "example",
  "LCT": "example",
  "Vehicle Number": "example"
}
headers = {"Content-Type": "application/json", "Authorization": "Bearer 1e7e84f7445182e624376f3b0913d0e3"}

response = requests.post(url, data=json.dumps(data), headers=headers)

if response.status_code == 200:
    print("Success:", response.text)
else:
    print("Error:", response.status_code, response.text)