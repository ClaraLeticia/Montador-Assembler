# Simulador de Assembler
Este repositório contém o código de um simulador de assembler desenvolvido para disciplina de Arquitetura e Organização de Computadores.

## Clonando o repositório
Para utilizar o código, primeiro clone o repositório em sua máquina local:

```bash
git clone https://github.com/
```

## Como utilizar 

Para utilizar o simualador de assembler, é necessário executar via linha de comando e requer dois parâmetros:

1. **Arquivo de entrada**: O arquivo `.asm` que contém as instruções a serem codificadas.
2. **Formato de saída**: O formato do arquivo de saída gerado.
   - `-b` para binário
   - `-h` para hexadecimal

### Exemplos de Uso

Para gerar um arquivo binário:

```bash
./montador teste.asm -b
```

Para gerar um arquivo hexadecimal:

```bash
./montador teste.asm -h
```

## Restrições de uso

Para arquivo `.asm` ser corretamente codificado, é necessário seguir as seguintes restrições:

1. **Registradores**: Não devem ser separados por espaços. Exemplo:
   - **Correto**:
     ~~~Assembly
     add $t0,$9,$10
     sll $s0,$s1,3
     lw $8,4($9)
     ~~~
   - **Incorreto**:
     ~~~Assembly
     add $t0, $9, $10
     sll $s0, $s1, 3
     lw $8, 4($9)
     ~~~

2. **Comentários**: Devem ser feitos na mesma linha da instrução. Não é permitido uma linha contendo apenas comentário.
   - **Correto**:
     ~~~Assembly
     add $t0,$9,$10 # soma os registradores
     ~~~
   - **Incorreto**:
     ~~~Assembly
     # somando os registradores
     add $t0,$9,$10
     ~~~

3. **Alinhamento das instruções**: Todas as instruções devem estar alinhadas à esquerda, sem tabs ou espaçamento no início da linha.
   - **Correto**:
     ~~~Assembly
     add $t0,$9,$10
     sub $t1,$4,$2
     ~~~
   - **Incorreto**:
     ~~~Assembly
         add $t0,$9,$10
     sub $t1,$4,$2
         sll $s0,$s1,3
     ~~~

4. **Labels**: Devem estar sozinhos na linha, com as instruções referentes ao label começando a partir da linha seguinte.
   - **Correto**:
     ~~~Assembly
     L1:
     add $t0,$9,$10
     sub $t1,$4,$2
     ~~~
   - **Incorreto**:
     ~~~Assembly
     L1: add $t0,$9,$10
     sub $t1,$4,$2
     ~~~
