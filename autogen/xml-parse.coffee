"use strict";

fs = require 'fs'
util = require 'util'

inspectObj = {showHidden: true, depth: null, colors: true}

console.inspect = (item)-> console.dir item, inspectObj

class choice
	constructor: (@choices...)->
	parse: (parser)=>
		startPos = parser.curPos()
		retVal = undefined
		for ch, ci in @choices
			retVal = parser.parseStmt(ch)
		#	console.dir {startPos: startPos, ci: ci, retVal: retVal, ch: ch}, inspectObj
			if retVal?
				return retVal
			else
				parser.curPosSet(startPos)

		return



class seq
	constructor: (@seq...)->
	parse: (parser)=>
		@matchStart = parser.curPos()

		for stmtn in @seq
			#console.log 'stmtn', stmtn
			objectType = getPrototypeConstructorName stmtn
			#console.log 'objectType:', objectType
			switch objectType
				when 'seq', 'range', 'plus', 'question', 'star', 'joinString', 'notPredicate', 'callProducer', 'inputBooleanMap', 'matchChars', 'setVariable'
					return unless parser.parseStmt(stmtn)?

				when 'testEQ'
					valA = switch stmtn.va
						when 'matchString' then parser.curStr()[@matchStart..parser.curPos() - 1]
						else parser.variables[stmtn.va]

					valB = switch stmtn.vb
						when 'matchString' then parser.curStr()[@matchStart..parser.curPos() - 1]
						else parser.variables[stmtn.vb]

					return unless valA is valB


				when 'inputBooleanMap'
					charCode = parser.curCharCode()
					switch stmtn.tfMap[charCode]
						when '1'
							parser.curPosOffset(1)
							#return String.fromCharCode charCode
						else
							return

				when 'returnLiteral'
					return stmtn.literalValue

				when 'returnVariable'
					switch stmtn.vname
						when 'matchString'
							return parser.curStr()[@matchStart..parser.curPos() - 1]
						else
							return parser.variables[stmtn.vname]
						#else throw new Error "returnVariable.vname: #{stmtn.vname}"

				when 'returnStaticKeyedObject'
					retVal = Object.create null
					for k, v of stmtn.vobj
						switch v
							when 'matchString'
								retVal[k] = parser.curStr()[@matchStart..parser.curPos() - 1]
							else
								if typeof v is 'string'
									retVal[k] = parser.variables[v]
								else
									retVal[k] = v

					return retVal

				else
					throw new Error "objectType: #{objectType}"

		return parser.curStr()[@matchStart..parser.curPos() - 1]

convertRangeStringToObject = (ts)->
#	console.log 'convertRangeStringToObject', arguments
	ot = []
	ps = 'start'
	sc = undefined
	mc = undefined
	for n in ts
		#console.log ps: ps, n: n, sc: sc, mc: mc, ot: ot
		switch ps
			when 'start'
				switch n
					when '-' then ot.push ('-').charCodeAt(0); continue;
					else sc = n; ps = 'middle'; continue;
			when 'middle'
				switch n
					when '-' then mc = n; ps = 'finish'; continue;
					else ot.push sc.charCodeAt(0); sc = undefined; ot.push n.charCodeAt(0); ps = 'start'; continue;
			when 'finish'
				ot.push [sc.charCodeAt(0), n.charCodeAt(0)]
				sc = undefined
				mc = undefined
				ps = 'start'
				continue
			else
				throw new Error "ps: #{ps}"

	switch ps
		when 'start' then
		when 'middle' then ot.push sc.charCodeAt(0); sc = undefined; ps = 'start';
		when 'finish' then ot.push sc.charCodeAt(0), mc.charCodeAt(0); sc = undefined; mc = undefined; ps = 'start';

	#console.log ps: ps, sc: sc, mc: mc, ot: ot
	return ot

class inputBooleanMap
	constructor: (options)->
		if arguments.length is 1 and typeof arguments[0] is 'string'
			options = t: convertRangeStringToObject(arguments[0])

		if arguments.length is 2 and typeof arguments[0] is 'string' and typeof arguments[1] is 'string'
			options =
				t: convertRangeStringToObject(arguments[0])
				f: convertRangeStringToObject(arguments[1])

		@tfMap = []

		if options.t?
			for ti in options.t
				switch typeof ti
					when 'object'
						#console.log 'ti object', ti
						low = if typeof ti[0] is 'number' then ti[0] else ti[0].charCodeAt(0)
						high = if typeof ti[1] is 'number' then ti[1] else ti[1].charCodeAt(0)

						#console.log "low: #{low}, high: #{high}"
						for tn in [Math.min(low, high)..Math.max(low, high)]
							@tfMap[tn] = true

						#console.log @tfMap

					when 'string'
						@tfMap[ti.charCodeAt(0)] = true
						#console.log @tfMap

					when 'number'
						@tfMap[ti] = true
						#console.log @tfMap

					else throw new Error "typeof ti: #{typeof ti}"

		if options.f?
			for fi in options.f
				switch typeof fi
					when 'object'
						#console.log 'fi object', fi
						low = if typeof fi[0] is 'number' then fi[0] else fi[0].charCodeAt(0)
						high = if typeof fi[1] is 'number' then fi[1] else fi[1].charCodeAt(0)

						#console.log "low: #{low}, high: #{high}"
						for fn in [Math.min(low, high)..Math.max(low, high)]
							@tfMap[fn] = false

						#console.log @tfMap

					when 'string'
						@tfMap[fi.charCodeAt(0)] = false
						#console.log @tfMap

					when 'number'
						@tfMap[fi] = false
						#console.log @tfMap

					else throw new Error "typeof fi: #{typeof fi}"

		for n, i in @tfMap
			#console.log i, n, typeof n
			switch typeof n
				when 'boolean' then continue
				when 'undefined' then @tfMap[i] = false

		@tfMap = ((if n then '1' else '0') for n in @tfMap).join('')

	parse: (parser)=>
		charCode = parser.curCharCode()
		switch @tfMap[charCode]
			when '1'
				parser.curPosOffset(1)
				return String.fromCharCode charCode
			else
				return

class matchChars
	constructor: (@chars)->
	parse: (parser)=>
		cs = parser.curStr()
		cp = parser.curPos()
		for n, i in @chars
			return unless n is cs[cp + i]

		parser.curPosOffset(@chars.length)
		return @chars

class range
	constructor: (@range...)->
	parse: (parser)=>
		#console.log 'range.parse', '@:', @, parser
		for ri in @range
			#console.log 'ri', ri
			switch typeof ri
				when 'object'
					#console.log 'parser', parser
					#console.log 'parser.curStr()', parser.curStr()
					#console.log ri[0].charCodeAt
					charCode = parser.curCharCode()
					if charCode >= ri[0].charCodeAt(0) and charCode <= ri[1].charCodeAt(0)
						parser.curPosOffset(1)
						#console.log 'ri success parser.curPos()', parser.curPos()
						return String.fromCharCode charCode

				when 'string'
					#console.log 'parser', parser
					#console.log 'parser.curStr()', parser.curStr()
					charCode = parser.curCharCode()
					if charCode is ri.charCodeAt(0)
						parser.curPosOffset(1)
						#console.log 'ri success parser.curPos()', parser.curPos()
						return String.fromCharCode charCode

				else throw Error "range ri #{ri} #{typeof ri}"
		console.log 'ri failure'
		return

class notPredicate
	constructor: (@stmt)->
	parse: (parser)=>
		startPos = parser.curPos()
		ret = parser.parseStmt(@stmt)
		parser.curPosSet(startPos)
		return if ret?
		return true

class joinString
	constructor: (@stmt)->
	parse: (parser)=>
		try
			return parser.parseStmt(@stmt).join('')
		catch err
			return

class repeat
	constructor: (@minRep, @maxRep, @stmt)->
	parse: (parser)=>
		startPos = parser.curPos()
		ret = []
		while (retVal = parser.parseStmt(@stmt))?
			#console.log 'retVal', retVal
			ret.push retVal
			#console.log 'ret', ret
			if ret.length is @maxRep then break

		#console.log 'ret', ret
		if ret.length >= @minRep then return ret
		parser.curPosSet(startPos)
		return

class plus
	constructor: (@stmt)->
	parse: (parser)=>
		startPos = parser.curPos()
		ret = []
		while (retVal = parser.parseStmt(@stmt))?
			#console.log 'retVal', retVal
			ret.push retVal
			#console.log 'ret', ret

		#console.log 'ret', ret
		if ret.length > 0 then return ret
		parser.curPosSet(startPos)
		return

class question
	constructor: (@stmt)->
	parse: (parser)=>
		startPos = parser.curPos()
		parser.curPosSet(startPos)
		ret = []
		while (retVal = parser.parseStmt(@stmt))?
			#console.log 'retVal', retVal
			ret.push retVal
			#console.log 'ret', ret
			break

		#console.log 'ret', ret
		if ret.length > 0 then return ret
		parser.curPosSet(startPos)
		return ret

class star
	constructor: (@stmt)->
	parse: (parser)=>
		startPos = parser.curPos()
		parser.curPosSet(startPos)
		ret = []
		while (retVal = parser.parseStmt(@stmt))?
			#console.log 'retVal', retVal
			ret.push retVal
			#console.log 'ret', ret

		#console.log 'ret', ret
		if ret.length > 0 then return ret
		parser.curPosSet(startPos)
		return ret

class isEqual
	constructor: (@argA, @argB)->

class str
	constructor: (@str)->

class vname
	constructor: (@vname)->

class callProducer
	constructor: (@pname, @args...)->
	parse: (parser)=>
		switch @pname
			when 'eof'
				return true if parser.curPos() is parser.curStr().length
				return
			else
				#console.log 'callProducer', @, parser
				tempVars = parser.variables
				parser.variables = Object.create null
				ret = parser.parse(@pname, parser.curStr(), parser.curPos())
				parser.variables = tempVars
				return ret


class producer
	constructor: (@pname, @args, @stmt)->

allGrammars = Object.create null

class grammar
	constructor: (obj)->
		for gname, gobj of obj
			producers = Object.create null
			allGrammars[gname] = producers
			for pname, stmt of gobj
				producers[pname] = new producer(pname, {}, stmt)

class setVariable
	constructor: (@vname, @stmt)->
	parse: (parser)=>
		retVal = parser.parseStmt(@stmt)
		return unless retVal?
		parser.variables[@vname] = retVal
	#	console.log '@vname': @vname, 'retVal': retVal, 'parser.variables': parser.variables, '@stmt': @stmt
		return retVal

class returnStaticKeyedObject
	constructor: (@vobj)->
	parse: (parser)=>
		retVal = Object.create null
		for k, v of @vobj
			retVal[k] = parser.variables[v]
		return retVal

class testEQ
	constructor: (@va, @vb)->

class returnLiteral
	constructor: (@literalValue)->

class returnVariable
	constructor: (@vname)->
	parse: (parser)=>
		switch @vname
			when 'matchString'
				return parser.matchString
			else throw new Error "@vname: #{@vname}"

getPrototypeConstructorName = (obj)->
	try
		return Object.getPrototypeOf(obj).constructor.name
	catch e
		return

class producerInstance
	constructor: (@proObj, @str, @pos)->

class parser
	constructor: (@grammarName)->
		@producerInstanceStack = []
		@variables = Object.create null

	curProducer: => @producerInstanceStack[@producerInstanceStack.length - 1].proObj
	curStr: => @producerInstanceStack[@producerInstanceStack.length - 1].str
	curPos: => @producerInstanceStack[@producerInstanceStack.length - 1].pos
	curChar: => @curStr()[@curPos()]
	curCharCode: => @curStr().charCodeAt(@curPos())
	curPosOffset: (offset)=>
		@producerInstanceStack[@producerInstanceStack.length - 1].pos += offset
		#console.log @producerInstanceStack[@producerInstanceStack.length - 1].pos

	curPosSet: (setPos)=>
		@producerInstanceStack[@producerInstanceStack.length - 1].pos = setPos
		#console.log setPos

	parse: (producerName, str, pos = 0)=>
		unless allGrammars[@grammarName][producerName]?
			throw new Error "allGrammars[@grammarName: #{@grammarName}][producerName: #{producerName}] missing"

		@producerInstanceStack.push new producerInstance(allGrammars[@grammarName][producerName], str, pos)
		@parseStmt @curProducer().stmt

	parseStmt: (stmt)=>
		objectType = getPrototypeConstructorName stmt
		#console.log 'objectType:', objectType
		switch objectType
			when 'seq', 'range', 'plus', 'question', 'star', 'joinString', 'notPredicate', 'returnVariable', 'callProducer', 'inputBooleanMap', 'matchChars', 'setVariable', 'choice', 'returnStaticKeyedObject' then stmt.parse @
			else throw new Error "objectType: #{objectType}"


new grammar xml:
	defaultInputType:   'utf-8'

	Attr: new seq(
		new plus(new callProducer('ws')),
		new setVariable('name', new callProducer('nodeName')),
		new star(new callProducer('ws')),
		new matchChars('='),
		new star(new callProducer('ws')),
		new setVariable('value', new callProducer('AttValue')),
		new returnStaticKeyedObject({name: 'name', value: 'value'}))

	dqVal: new joinString(new star(new choice(
				new inputBooleanMap('\u0000-\u007f', '<&"'),
				new callProducer('EntityQUOT'),
				new callProducer('EntityAMP'),
				new callProducer('EntityAPOS'),
				new callProducer('EntityLT'),
				new callProducer('EntityGT'))))

	sqVal: new joinString(new star(new choice(
				new inputBooleanMap('\u0000-\u007f', "<&'"),
				new callProducer('EntityQUOT'),
				new callProducer('EntityAMP'),
				new callProducer('EntityAPOS'),
				new callProducer('EntityLT'),
				new callProducer('EntityGT'))))

	EntityRef: new seq(new matchChars('&'), new callProducer('nodeName'), new matchChars(';'), new returnVariable('matchString'))

	EntityQUOT: new seq(new matchChars('&quot;'), new returnLiteral('"'))
	EntityAMP: new seq(new matchChars('&amp;'), new returnLiteral('&'))
	EntityAPOS: new seq(new matchChars('&apos;'), new returnLiteral("'"))
	EntityLT: new seq(new matchChars('&lt;'), new returnLiteral('<'))
	EntityGT: new seq(new matchChars('&gt;'), new returnLiteral('>'))

	CharDataPlus: new seq(new plus(new inputBooleanMap('\u0000-\u007f', '<&')), new returnVariable('matchString'))
	CharDataPlusWithEntities: new joinString(new plus(new choice(
				new inputBooleanMap('\u0000-\u007f', '<&'),
				new callProducer('EntityQUOT'),
				new callProducer('EntityAMP'),
				new callProducer('EntityAPOS'),
				new callProducer('EntityLT'),
				new callProducer('EntityGT'))))

	CommentDataStar: new seq(
		new star(
			new seq(
				new notPredicate(new matchChars('--')),
				new inputBooleanMap('\u0000-\u007f', '')
			)
		),
		new returnVariable('matchString')
	)

	AttValue: new choice(
		new seq(
			new matchChars('"'),
			new setVariable('value', new callProducer('dqVal')),
			new matchChars('"'),
			new returnVariable('value')),
		new seq(
			new matchChars("'"),
			#new star(new inputBooleanMap(t: [[0x00, 0x7f]], f: ['<', '&', "'"])),
			new setVariable('value', new callProducer('sqVal')),
			new matchChars("'"),
			new returnVariable('value')))

	nodeName: new seq(
		new inputBooleanMap(t: [['a','z'], ['A', 'Z']]),
		new plus(new inputBooleanMap(t: [['a','z'], ['A','Z'], ['0','9'], '_', '-'])),
		new returnVariable('matchString'))

	ws: new seq(new plus(new inputBooleanMap(' \r\n')), new returnVariable('matchString'))

	nodeEmpty: new seq(
		new matchChars('<'),
		new setVariable('nodeName', new callProducer('nodeName')),
		new setVariable('attributes', new star(new callProducer('Attr'))),
		new star(new callProducer('ws')),

		new matchChars('/>'),
		new returnStaticKeyedObject({nodeName: 'nodeName', attributes: 'attributes', childNodes: []})
		)

	processingIntruction: new seq(
		new matchChars('<?'),
		new setVariable('nodeName', new callProducer('nodeName')),
		new setVariable('attributes', new star(new callProducer('Attr'))),
		new star(new callProducer('ws')),

		new matchChars('?>'),
		new star(new callProducer('ws')),
		new returnStaticKeyedObject({nodeName: 'nodeName', attributes: 'attributes', childNodes: []})
	)


	comment: new seq(
		new matchChars('<!--'),
		new setVariable('comment', new callProducer('CommentDataStar')),
		new matchChars('-->'),
		new returnStaticKeyedObject({comment: 'comment'})
		)

	nodeStart: new seq(
		new matchChars('<'),
		new setVariable('n', new callProducer('nodeName')),
		new matchChars('>'),
		new returnVariable('n'))

	nodeEnd: new seq(
		new matchChars('</'),
		new setVariable('n', new callProducer('nodeName')),
		new matchChars('>'),
		new returnVariable('n'))

	node: new choice(
		new setVariable('entityRef', new callProducer('EntityRef')),
		new setVariable('text', new callProducer('CharDataPlusWithEntities')),
		new setVariable('comment', new callProducer('comment')),
		new callProducer('nodeEmpty'),
		new seq(
			new matchChars('<'),
			new setVariable('ns', new callProducer('nodeName')),
			new setVariable('attributes', new star(new callProducer('Attr'))),
			new star(new callProducer('ws')),
			new matchChars('>'),
			new setVariable('nk', new star(new callProducer('node'))),
			new matchChars('</'),
			new setVariable('ne', new callProducer('nodeName')),
			new matchChars('>'),
			new testEQ('ns', 'ne'),
			new returnStaticKeyedObject({nodeName: 'ns', attributes: 'attributes', childNodes: 'nk'})))

	document: new seq(
		new question(new callProducer('processingIntruction')),
		new setVariable('node', new plus(new callProducer('node'))),
		new returnVariable('node')
	)

	documentWithEOF: new seq(
		new question(new callProducer('processingIntruction')),
		new setVariable('node', new plus(new callProducer('node'))),
		new callProducer('eof'),
		new returnVariable('node')
	)


#console.log util.inspect allGrammars, inspectObj

parseXmlString = (parserName, producerName, xmlString)->
	console.log "parserName: '#{parserName}', producerName: '#{producerName}', xmlString: #{JSON.stringify(xmlString)}"
	console.inspect new parser(parserName).parse(producerName, xmlString)
	console.log ''

parseXmlFile = (parserName, producerName, fileName)->
	console.log "parserName: '#{parserName}', producerName: '#{producerName}', fileName: '#{fileName}'"
	#console.log new Buffer(fs.readFileSync(fileName, 'utf-8')[0..2])
	#console.inspect new parser(parserName).parse(producerName, fs.readFileSync(fileName, 'utf-8'))
	ret = new parser(parserName).parse(producerName, fs.readFileSync(fileName, 'utf-8'))
	fs.writeFileSync(fileName + '.json', JSON.stringify(ret, null, '\t'))
	#console.log ''

https = require('https')

https.get 'https://raw.githubusercontent.com/KhronosGroup/Vulkan-Docs/1.0/src/spec/vk.xml', (response)->
	response.pipe fs.createWriteStream('./vk.xml')
	response.on 'end', ->
		parseXmlFile('xml', 'documentWithEOF', './vk.xml')
