Todas as funcionalidades foram implementadas, excepto a opção de remover
pacotes de viagens.
Não faria sentido fazê-lo com o modo como o valor total é calculado/guardado neste momento.

Algumas das melhorias não implementadas são:

	Restrições no destino de novos/alterados pacotes.
	Permitir filtrar destino ignorando maiúsculas/minúsculas.

	Mais restrições no input de moradas.

	Datas mais restritas (anos bissextos, numero de dias de cada mês).
	Gerir disponibilidade dos pacotes consoante a data actual do sistema.

	Existência de bastante código redundante entre Menus (particularmente cliente e pacote).
	Remover lógica dos menus para controladores próprios.

	Mudar estrutura dos pacotes comprados de vector para map com id como chave.

	Guardar conteúdo actual dos ficheiros (duplicar ficheiro temporariamente por exemplo) antes
	de abrir os ficheiros com "trunc" na altura de guardar alterações.