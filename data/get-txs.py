import requests
import json

url = 'https://fullnode.devnet.sui.io:443'

headers = {
  'Content-Type': 'application/json'
}

all_tx_digests = set()

def get_tx_of_obj(obj_id):
  payload_o = {
    "jsonrpc": "2.0",
    "id": 1,
    "method": "sui_getObject",
    "params": [obj_id]
  }
  res = json.loads(
    requests.request('POST', url, headers=headers, data=json.dumps(payload_o)).text
  )['result']
  
  if res['status'] != 'Exists':
    return

  tx_id = res['details']['previousTransaction']
  get_tx(tx_id)

def get_tx(tx):
  if tx[::-1] == '=': return
  if tx in all_tx_digests: return
  if len(tx) != 44: return

  print(tx)
  all_tx_digests.add(tx)
  
  # try:
  #   res = json.loads(
  #     requests.request('POST', url, headers=headers, data=json.dumps(payload)).text
  #   )
  #   print(tx)
  #   # print(res)
  # except BaseException as e:
  #   print(e)
  #   return
  
  # if 'error' in res: return

  # effects = res['result']['effects']
  # print(effects)

  # if 'created' in effects:
  #   for cr in effects['created']:
  #     obj_id = cr['reference']['objectId']
  #     # get_tx_of_obj(obj_id)
  
  # if 'mutated' in effects:
  #   for mt in effects['mutated']:
  #     obj_id = mt['reference']['objectId']
  #     # get_tx_of_obj(obj_id)
  
  # if 'sharedObjects' in effects:
  #   for obj in effects['sharedObjects']:
  #     get_tx(obj['objectId'])
  
  # if 'gasObject' in effects:
  #   obj_id = effects['gasObject']['reference']['objectId']
  #   get_tx(obj_id)

objs = list()
with open('./obj-list.csv', 'r') as f:
	objs = f.read().split(',')

for obj in objs:
  payload = json.dumps([
    {
      "method": "sui_getTransactions",
      "jsonrpc": "2.0",
      "params": [
        {
          "InputObject": obj
        },
        None,
        None,
        True
      ],
      "id": "706c2e48-8d90-46df-b12d-0e5dc83ab71b"
    },
    {
      "method": "sui_getTransactions",
      "jsonrpc": "2.0",
      "params": [
        {
          "MutatedObject": obj
        },
        None,
        None,
        True
      ],
      "id": "2303303d-c1bc-4df4-b3f0-d54daba7d1ea"
    }
  ])
  res = json.loads(
    requests.request('POST', url, headers=headers, data=payload).text
  )
  txs = list(set(res[0]['result']['data'] + res[1]['result']['data']))

  for tx in txs:
    get_tx(tx)

with open('./tx-list.csv', 'w') as f:
  f.write(','.join(all_tx_digests))

