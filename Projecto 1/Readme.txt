Todas as funcionalidades foram implementadas, excepto a op��o de remover
pacotes de viagens.
N�o faria sentido faz�-lo com o modo como o valor total � calculado/guardado neste momento.

Algumas das melhorias n�o implementadas s�o:

	Restri��es no destino de novos/alterados pacotes.
	Permitir filtrar destino ignorando mai�sculas/min�sculas.

	Mais restri��es no input de moradas.

	Datas mais restritas (anos bissextos, numero de dias de cada m�s).
	Gerir disponibilidade dos pacotes consoante a data actual do sistema.

	Exist�ncia de bastante c�digo redundante entre Menus (particularmente cliente e pacote).
	Remover l�gica dos menus para controladores pr�prios.

	Mudar estrutura dos pacotes comprados de vector para map com id como chave.

	Guardar conte�do actual dos ficheiros (duplicar ficheiro temporariamente por exemplo) antes
	de abrir os ficheiros com "trunc" na altura de guardar altera��es.