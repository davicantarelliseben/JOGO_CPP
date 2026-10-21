all :
	g++ main.cpp Character.cpp Player.cpp Enemy.cpp -Iinclude -o a.exe
	./a.exe

.PHONY: commit

commit:
	@echo Digite a mensagem do commit:
	@set /p msg="" && cmd /v:on /c "git add . && git commit -m "!msg!" && git push origin main"