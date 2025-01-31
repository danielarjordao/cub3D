# Planejamento do Projeto Cub3D

## 1. Configuração Inicial (src/utils/init_data.c)
Configuração inicial do jogo:
- Inicializar a biblioteca MiniLibX.
- Criar a janela com `mlx_new_window`.
- Configurar estruturas de dados para:
  - Mapa.
  - Texturas (paredes, chão, etc.).
  - Configurações globais.
  - Configurações do jogo.

## 2. Carregamento e Validação do Mapa (src/parsing/parsing.c)
Carregar e validar o mapa:
- Validar o formato do arquivo `.cub`.
- Verificar cumprimento das regras do mapa.
- Verificar a jogabilidade.
- Ler e armazenar os dados do mapa em uma estrutura interna.

## 3. Implementação do Raycasting (src/raycasting/raycasting.c)
Implementar o raycasting:
- Calcular a projeção 3D utilizando o algoritmo DDA (Digital Differential Analyzer) de raycasting.

## 4. Carregamento de Texturas (src/raycasting/render.c)
Carregar e aplicar texturas:
- Carregar as texturas com `mlx_xpm_file_to_image`.
- Aplicar as texturas.

## 5. Início do Jogo (src/game/start_game.c)
Iniciar o jogo:
- Preparar o loop principal de jogo.

## 6. Controle do Jogador e Interatividade (src/game/handle_events.c)
Adicionar controle ao jogador:
- Configurar teclas de interação.
- Gerenciar os movimentos do jogador.

## 7. Liberação de Memória (src/utils/free_mem.c)
Liberar memória corretamente:
- Garantir que não haja vazamentos de memória ao finalizar o jogo.


---

# Estrutura de Pastas

## Diretório Principal
- `cub3d/`: Diretório raiz do projeto.

## Subdiretórios

- **includes/**: Arquivos de cabeçalho.
  - `cub3d.h`: Cabeçalho principal.
  - `utils.h`: Funções auxiliares.
  - `parsing.h`: Funções de parsing do mapa.
  - `raycasting.h`: Funções de raycasting.
  - `game.h`: Funções do jogo.

- **lib/**: Bibliotecas externas.
  - `minilibx/`: MiniLibX.
  - `libft/`: Biblioteca utilitária.

- **maps/**: Arquivos de mapas testes.

- **objs/**: Arquivos de objeto `.o`.

- **src/**: 
  - **utils/**: Funções auxiliares.
    - `init_data.c`: Configuração inicial do jogo.
    - `free_mem.c`: Liberação de memória.
    - `utils.c`: Outras funções auxiliares.
  
  - **parsing/**: Carregamento e validação do mapa.
    - `parsing.c`: Lê e valida o mapa.
  
  - **raycasting/**: Lógica de raycasting.
    - `raycasting.c`: Implementa o raycasting.
    - `render.c`: Carrega e aplica texturas no ambiente.

  - **game/**: Lógica do jogo e controle do jogador.
    - `start_game.c`: Inicia loop principal do jogo.
    - `handle_events.c`: Gerencia eventos de entrada e movimentação.
  
  - **main.c**: Função principal que inicializa e executa o jogo.

- **textures/**: Texturas do jogo.
  - `textures.xpm`: Texturas para paredes, chão, jogador, etc.

- **Makefile**: Arquivo de compilação.
