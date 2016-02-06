#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import xml.etree.ElementTree as ET

input_list = []

for arg in sys.argv[1:]:
	input_list.append(arg)

if len(input_list) < 1:
	print 'usage: makerst.py <classes.xml>'
	sys.exit(0)


def validate_tag(elem, tag):
	if elem.tag != tag:
		print "Tag mismatch, expected '" + tag + "', got " + elem.tag
		sys.exit(255)


class_names = []
classes = {}

def ul_string(str,ul):
	str+="\n"
	for i in range(len(str)-1):
		str+=ul
	str+="\n"
	return str

def make_class_list(class_list, columns):

	f = open('class_list.rst', 'wb')
	prev = 0
	col_max = len(class_list) / columns + 1
	print ('col max is ', col_max)
	col_count = 0
	row_count = 0
	last_initial = ''
	fit_columns = []

	for n in range(0, columns):
		fit_columns += [[]]

	indexers = []
	last_initial = ''

	idx = 0
	for n in class_list:
		col = idx / col_max
		if col >= columns:
			col = columns - 1
		fit_columns[col] += [n]
		idx += 1
		if n[:1] != last_initial:
			indexers += [n]
		last_initial = n[:1]

	row_max = 0
	f.write("\n")
	
	for n in range(0, columns):
		if len(fit_columns[n]) > row_max:
			row_max = len(fit_columns[n])

	f.write("| ")
	for n in range(0, columns):
		f.write(" | |")

	f.write("\n")		
	f.write("+")
	for n in range(0, columns):
		f.write("--+-------+")
	f.write("\n")

	for r in range(0, row_max):
		s = '+ '
		for c in range(0, columns):
			if r >= len(fit_columns[c]):
				continue

			classname = fit_columns[c][r]
			initial = classname[0]
			if classname in indexers:
				s += '**' + initial + '** | '
			else:
				s += ' | '

			s += '[' + classname + '](class_'+ classname.lower()+') | '

		s += '\n'
		f.write(s)

	for n in range(0, columns):
		f.write("--+-------+")
	f.write("\n")


def rstize_text(text,cclass):
	pos = 0
	while True:
		pos = text.find('[', pos)
		if pos == -1:
			break

		endq_pos = text.find(']', pos + 1)
		if endq_pos == -1:
			break

		pre_text = text[:pos]
		post_text = text[endq_pos + 1:]
		tag_text = text[pos + 1:endq_pos]

		if tag_text in class_names:
			tag_text = make_type(tag_text)
		else:

		# command

			cmd = tag_text
			space_pos = tag_text.find(' ')
			if cmd.find('html') == 0:
				cmd = tag_text[:space_pos]
				param = tag_text[space_pos + 1:]
				tag_text =  param 
			elif cmd.find('method') == 0:
				cmd = tag_text[:space_pos]
				param = tag_text[space_pos + 1:]

				if param.find('.') != -1:
					(class_param, method_param) = param.split('.')
					tag_text = ':ref:`'+class_param+'.'+method_param+'<' + class_param.lower() + '_' + method_param + '>`'
				else:
					tag_text = ':ref:`' + param + '<' + cclass +"_"+ param + '>`'
			elif cmd.find('image=') == 0:
				tag_text = "" #'![](' + cmd[6:] + ')'
			elif cmd.find('url=') == 0:
				tag_text = ':ref:`' + cmd[4:] + '<'+cmd[4:]+">`"
			elif cmd == '/url':
				tag_text = ')'
			elif cmd == 'center':
				tag_text = ''
			elif cmd == '/center':
				tag_text = ''
			elif cmd == 'br':
				tag_text = '\n| '
			elif cmd == 'i' or cmd == '/i':
				tag_text = '*'
			elif cmd == 'b' or cmd == '/b':
				tag_text = '**'
			elif cmd == 'u' or cmd == '/u':
				tag_text = ''
			else:
				tag_text = ':ref:`' + tag_text + '<class_'+tag_text.lower()+'>`'

		text = pre_text + tag_text + post_text
		pos = len(pre_text) + len(tag_text)

 # tnode = ET.SubElement(parent,"div")
 # tnode.text=text

	return text


def make_type(t):
	global class_names
	if t in class_names:
		return ':ref:`'+t+'<class_' + t.lower()+'>`'
	return t


def make_method(
	f,
	name,
	m,
	declare,
	cname,
	event=False,
	pp=None
	):

	if (declare or pp==None):
		t = '- '
	else:
		t = ""
		
	ret_type = 'void'
	args = list(m)
	mdata = {}
	mdata['argidx'] = []
	for a in args:
		if a.tag == 'return':
			idx = -1
		elif a.tag == 'argument':
			idx = int(a.attrib['index'])
		else:
			continue

		mdata['argidx'].append(idx)
		mdata[idx] = a

	if not event:
		if -1 in mdata['argidx']:
			t += make_type(mdata[-1].attrib['type'])
		else:
			t += 'void'
		t += ' '

	if declare or pp==None:

		# span.attrib["class"]="funcdecl"
		# a=ET.SubElement(span,"a")
		# a.attrib["name"]=name+"_"+m.attrib["name"]
		# a.text=name+"::"+m.attrib["name"]

		s = ' **'+m.attrib['name']+'** '
	else:
		s = ':ref:`'+ m.attrib['name']+'<class_' + cname+"_"+m.attrib['name'] + '>` '
		

	s += ' **(**'
	argfound = False
	for a in mdata['argidx']:
		arg = mdata[a]
		if a < 0:
			continue
		if a > 0:
			s += ', '
		else:
			s += ' '

		s += make_type(arg.attrib['type'])
		if 'name' in arg.attrib:
			s += ' ' + arg.attrib['name']
		else:
			s += ' arg' + str(a)

		if 'default' in arg.attrib:
			s += '=' + arg.attrib['default']

		argfound = True

	if argfound:
		s += ' '
	s += ' **)**'

	if 'qualifiers' in m.attrib:
		s += ' ' + m.attrib['qualifiers']

#	f.write(s)
	if (not declare):
		if (pp!=None):
			pp.append( (t,s) )
		else:	
			f.write("- "+t+" "+s+"\n")
	else:
		f.write(t+s+"\n")


def make_rst_class(node):

	name = node.attrib['name']

	f = open("class_"+name.lower() + '.rst', 'wb')

	f.write(".. _class_"+name+":\n")
	f.write(name + '  \n==========\n')

	if 'inherits' in node.attrib:
		inh = node.attrib['inherits'].strip()
		f.write('**Inherits:** '+make_type(inh)+'\n---------\n')
	if 'category' in node.attrib:
		f.write('**Category:** ' + node.attrib['category'].strip()
				+ '\n---------\n')

	briefd = node.find('brief_description')
	if briefd != None:
		f.write('\n Brief Description  \n-------\n')
		f.write(rstize_text(briefd.text.strip(),name) + '\n')

	methods = node.find('methods')

	if methods != None and len(list(methods)) > 0:
		f.write('\nMember Functions \n---------\n')
		ml=[]
		for m in list(methods):
			make_method(f, node.attrib['name'], m, False,name,False,ml)
		longest_t = 0
		longest_s = 0
		for s in ml:
			sl = len(s[0])
			if (sl>longest_s):
				longest_s=sl
			tl = len(s[1])
			if (tl>longest_t):
				longest_t=tl
				
		sep="+"
		for i in range(longest_s+2):
			sep+="-"
		sep+="+"
		for i in range(longest_t+2):
			sep+="-"
		sep+="+\n"
		f.write(sep)
		for s in ml:
			rt = s[0]
			while( len(rt) < longest_s ):
				rt+=" "
			st = s[1]
			while( len(st) < longest_t ):
				st+=" "
			f.write("| "+rt+" | "+st+" |\n")
			f.write(sep)
			
		

	events = node.find('signals')
	if events != None and len(list(events)) > 0:
		f.write('\nSignals  \n----------\n')
		for m in list(events):
			make_method(f, node.attrib['name'], m, True,name, True)

	members = node.find('members')

	if members != None and len(list(members)) > 0:
		f.write('\nMember Variables  \n--------\n')

		for c in list(members):
			s = '- '
			s += make_type(c.attrib['type']) + ' '
			s += '**' + c.attrib['name'] + '**'
			if c.text.strip() != '':
				s += ' - ' + c.text.strip()
			f.write(s + '\n')

	constants = node.find('constants')
	if constants != None and len(list(constants)) > 0:
		f.write('\nNumeric Constants  \n------\n')
		for c in list(constants):
			s = '- '
			s += '**' + c.attrib['name'] + '**'
			if 'value' in c.attrib:
				s += ' = **' + c.attrib['value'] + '**'
			if c.text.strip() != '':
				s += ' - ' + c.text.strip()
			f.write(s + '\n')

	descr = node.find('description')
	if descr != None and descr.text.strip() != '':
		f.write('\nDescription  \n-------\n')
		f.write(rstize_text(descr.text.strip(),name) + '\n')

	methods = node.find('methods')

	if methods != None and len(list(methods)) > 0:
		f.write('\nMember Function Description  \n----------\n')
		for m in list(methods):
			f.write("\n.. _class_"+name+"_"+m.attrib['name']+":\n")
#			f.write(ul_string(m.attrib['name'],"^"))
			d = m.find('description')
			if d == None or d.text.strip() == '':
				continue
			#f.write('\n<a name="'+m.attrib['name']+'">' + m.attrib['name'] + '</a>\n------\n')
			make_method(f, node.attrib['name'], m, True,name)
			f.write('\n')
			f.write(rstize_text(d.text.strip(),name))
			f.write('\n')


for file in input_list:
	tree = ET.parse(file)
	doc = tree.getroot()

	if 'version' not in doc.attrib:
		print "Version missing from 'doc'"
		sys.exit(255)

	version = doc.attrib['version']

	for c in list(doc):
		if c.attrib['name'] in class_names:
			continue
		class_names.append(c.attrib['name'])
		classes[c.attrib['name']] = c

class_names.sort()

make_class_list(class_names, 2)

for cn in class_names:
	c = classes[cn]
	make_rst_class(c)

