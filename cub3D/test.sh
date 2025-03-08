#!/bin/bash

NAME="cub3D"

# Função para exibir mensagens com cores
print_message() {
	local color="$1"
	local message="$2"
	echo -e "\033[${color}m$message\033[0m"
}

# Verifica se o programa foi compilado
if [ ! -f "./$NAME" ]; then
	print_message "31" "Erro: O programa $NAME não foi encontrado. Certifique-se de que ele foi compilado."
	exit 1
fi

# Caminho para a pasta de mapas inválidos
MAP_DIR1="maps/invalid/"

# Caminho para a pasta de mapas válidos
MAP_DIR2="maps/valid/"

# Função para executar o Valgrind em um mapa
run_valgrind() {
	local MAP_FILE=$1
	echo -e "\n\033[1;34m[INFO] Executando Valgrind no arquivo $MAP_FILE\033[0m"
	valgrind --quiet --leak-check=full --show-leak-kinds=all "./$NAME" "$MAP_FILE"
	echo -e "\n\033[1;32m[INFO] Teste concluído. Pressione Enter para continuar para o próximo teste...\033[0m"
	read  # Aguardando a confirmação para continuar
}

# Cabeçalho de inicialização
print_message "1;33" "=============================="
print_message "1;33" "Iniciando o script de testes..."
print_message "1;33" "=============================="

# Escolha do usuário para qual pasta testar
echo -e "\n\033[1;34mEscolha uma opção de teste:\033[0m"
echo -e "1) Testar mapas inválidos"
echo -e "2) Testar mapas válidos"
echo -e "Digite o número da opção desejada e pressione Enter: "
read choice

# Executa os testes com base na escolha do usuário
case $choice in
	1)
		print_message "1;35" "=============================="
		print_message "1;35" "Iniciando os testes de mapas inválidos..."
		print_message "1;35" "=============================="
		# Itera sobre todos os arquivos na pasta de mapas inválidos
		if [ "$(ls -A $MAP_DIR1)" ]; then
			for MAP_FILE in "$MAP_DIR1"*; do
				if [ -f "$MAP_FILE" ]; then
					run_valgrind "$MAP_FILE"

				fi
			done
		else
			print_message "31" "Nenhum arquivo encontrado na pasta $MAP_DIR1"
		fi
		;;
	2)
		print_message "1;35" "=============================="
		print_message "1;35" "Iniciando os testes de mapas válidos..."
		print_message "1;35" "=============================="
		# Itera sobre todos os arquivos na pasta de mapas válidos
		if [ "$(ls -A $MAP_DIR2)" ]; then
			for MAP_FILE in "$MAP_DIR2"*; do
				if [ -f "$MAP_FILE" ]; then
					run_valgrind "$MAP_FILE"
				fi
			done
		else
			print_message "31" "Nenhum arquivo encontrado na pasta $MAP_DIR2"
		fi
		;;
	*)
		print_message "31" "Opção inválida. Por favor, escolha 1 ou 2."
		exit 1
		;;
esac

# Finalização do script
print_message "1;33" "=============================="
print_message "1;33" "Todos os testes foram concluídos."
print_message "1;33" "=============================="
