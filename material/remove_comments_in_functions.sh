#!/bin/bash

# Verifica se o caminho da pasta foi fornecido
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <caminho_da_pasta>"
    exit 1
fi

# Muda para o diretório especificado
if ! cd "$1"; then
    echo "Erro: Não foi possível acessar o diretório '$1'."
    exit 1
fi

# Atualiza status
git status >/dev/null 2>&1

# Verifica se há arquivos untracked ou modificados
if ! git diff-index --quiet HEAD -- || [ -n "$(git ls-files --others --exclude-standard)" ]; then
    echo "Erro: Há arquivos untracked ou modificados no repositório."
    echo "Por favor, faça commit ou stash das alterações antes de executar o script."
    exit 1
fi

# Criar ou recriar a branch "comments" com o conteúdo da branch atual
if git rev-parse --verify norminette >/dev/null 2>&1; then
    echo "A branch 'norminette' já existe. Excluindo-a..."
    git branch -D norminette
fi
echo "Criando a branch 'norminette' com o conteúdo da branch atual..."
git branch norminette
git checkout norminette

# Apagar comentários iniciados com "//" apenas dentro de funções
find . -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    awk '
    BEGIN { inside_function = 0; brace_count = 0 }
    /^[[:space:]]*{/ {  # Detecta abertura de bloco
        brace_count++;
        if (brace_count == 1) inside_function = 1;
    }
    /^[[:space:]]*}/ {  # Detecta fechamento de bloco
        brace_count--;
        if (brace_count == 0) inside_function = 0;
    }
    inside_function && /^[[:space:]]*\/\// { next }  # Remove comentários dentro de funções
    { print }  # Imprime todas as outras linhas
    ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
done

# Adicionar as alterações ao índice do Git
git add .

# Criar um novo commit com a mensagem apropriada
git commit -m "Remove comments inside functions"

# Voltar para a branch original
git checkout -

echo "Linhas de comentários iniciadas com '//' foram removidas."
