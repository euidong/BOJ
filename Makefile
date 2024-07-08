if [ -z ${exp} ];then exp='py'; fi

cpm:
ifdef no
	mkdir $(no)
	touch $(no)/main.$(exp)
	@echo 'success'
else
	@echo 'no number specified'
endif