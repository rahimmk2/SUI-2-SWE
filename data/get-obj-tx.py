import requests
import json

url = 'https://fullnode.devnet.sui.io:443'

headers = {
  'Content-Type': 'application/json'
}

obj = '0x57e31e5ec13b10a548a957275b7d21504ddbba08'

all_tx_digests = set()
def get_obj_res(vf, vt):
	payload = []
	for v in range(vf, vt + 1):
		payload.append({
			"jsonrpc": "2.0",
			"id": 1,
			"method": "sui_tryGetPastObject",
			"params": [obj, v]
		})
		
	res = json.loads(
    requests.request('POST', url, headers=headers, data=json.dumps(payload)).text
  )
	return res

for i in range(25000, 25400, 100):
	res = get_obj_res(i, i + 99)
	for r in res:
		if 'result' in r and r['result']['status'] == 'VersionFound':
			# print(r)
			all_tx_digests.add(r['result']['details']['previousTransaction'])

with open('./tx-list-obj.csv', 'w') as f: # Opening the CSV
  f.write(','.join(all_tx_digests))



