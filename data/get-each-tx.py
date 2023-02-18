import requests
import csv
import json
# Data Parsing
url = 'https://fullnode.devnet.sui.io:443'

payload = {
  'jsonrpc': '2.0',
  'id': 1,
  'method': 'sui_getTransaction',
  'params': []
}

headers = {
  'Content-Type': 'application/json'
}

used = {}
def get_obj_prev_tx(obj_id, obj_version):
	key = '{}__{}'.format(obj_id, obj_version)
	if key in used:
		return used[key]

	payload = {
		'jsonrpc': '2.0',
		'id': 1,
		'method': 'sui_tryGetPastObject',
		'params': [obj_id, obj_version - 1 if obj_version > 0 else 0]
	}
	print(obj_id, obj_version - 1 if obj_version > 0 else 0)
	res = json.loads(
		requests.request('POST', url, headers=headers, data=json.dumps(payload)).text
	)['result']

	used[key] = res['details']['previousTransaction'] if res['status'] == 'VersionFound' else 'NULL'
	return used[key]

txs = list()
with open('./tx-list-obj.csv', 'r') as f:
	txs = f.read().split(',')

f = open('./tx-data-obj.csv', 'w')
writer = csv.writer(f, lineterminator='\n')

writer.writerow([
	'transaction_digest',
	'timestamp_ms',
	'shared_objects_tx_digest',
	'shared_objects_str',
	'created_str',
	'mutated_str',
	'gas_used'
])

# k = 0
for tx in txs:
	# if k == 10: break

	payload['params'] = [tx]
	print(tx)

	res = json.loads(
		requests.request('POST', url, headers=headers, data=json.dumps(payload)).text
	)['result']
	# print(res)

	effects = res['effects']

	timestamp_ms = str(res['timestamp_ms'])

	gas_used = str(effects['gasUsed']['computationCost'] + effects['gasUsed']['storageCost'] + effects['gasUsed']['storageRebate'])

	created_str = ''
	if 'created' in effects:
		created = effects['created']
		created_str = []

		for cr in created:
			obj = cr['reference']
			created_str.append(
				' '.join([
					obj['objectId'],
					str(obj['version']),
					get_obj_prev_tx(obj['objectId'], obj['version']),
					# either the object owner or 'SHARED'
					cr['owner']['AddressOwner'] if 'AddressOwner' in cr['owner'] else 'SHARED',
				])
			)
		
		created_str = '|'.join(created_str)

	shared_objects_str = ''
	shared_objects_tx_digest = ''
	if 'sharedObjects' in effects:
		shared_objects = effects['sharedObjects']
		if 'transactionDigest' in shared_objects:
			shared_objects_tx_digest = shared_objects['transactionDigest']
		shared_objects_str = []
		
		for obj in shared_objects:
			shared_objects_str.append('{} {} {}'.format(
				obj['objectId'],
				str(obj['version']),
				get_obj_prev_tx(obj['objectId'], obj['version'])
			))

		shared_objects_str = '|'.join(shared_objects_str)

	mutated_str = ''
	if 'mutated' in effects:
		mutated = effects['mutated']
		mutated_str = []

		for mut in mutated:
			obj = mut['reference']
			mutated_str.append(
				' '.join([
					obj['objectId'],
					str(obj['version']),
					get_obj_prev_tx(obj['objectId'], obj['version']),
					# either the object owner or 'SHARED'
					mut['owner']['AddressOwner'] if 'AddressOwner' in mut['owner'] else 'SHARED',
				])
			)
		
		mutated_str = '|'.join(mutated_str)

	writer.writerow([
		tx, # transaction digest
		timestamp_ms, # timestamp in ms
    shared_objects_tx_digest, # shared objects transaction digest
    shared_objects_str, # shared objects info string
		created_str, # created objs info string
    mutated_str, # mutated objs info string
		gas_used
	])

	# k += 1

f.close()