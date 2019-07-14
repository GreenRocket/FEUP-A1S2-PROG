Todas as funcionalidades foram implementadas.

Algumas considerações não implementadas:
    Melhores restrições no destino de novos/alterados pacotes
	Permitir filtrar destino ignorando maiusculas/minusculas

	Mais controlo no input de moradas

	Ainda existe algum codigo redundante entre Menus
		
	Estrutura dos pacotes comprados seria talvez melhor como um "map<unsigned, TravelPack>", usando o id do pacote como chave
		
	Uma vez que se escreve por cima dos ficheiros, 
antes de os abrir com "trunc" na altura de guardar alterações,
fazer "backup" para não perder dados em caso de erro.


Para os pontos 9 e 10:
Utilização de um struct "location" para definir um local
É constituido por:
    nome,
    quais os pacotes que passam por esse local,
    nº de vezes que os respectivos pacotes foram comprados

É gerado um "map<string, location>" (chave = nome do local) de acordo com os ficheiros de pacotes/clientes.
Quando algum pacote/cliente é adicionado,alterado,removido ou quando uma compra é feita, o local é atualizado de acordo.

Com base neste struct, é facíl obter os locais mais visitados e a que pacotes pertencem esses locais.

