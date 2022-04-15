cpm:
ifdef no
	mkdir $(no)
	touch $(no)/main.py
	@echo 'success'
else
	@echo 'no number specified'
endif