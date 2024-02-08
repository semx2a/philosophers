ifndef OUTPUT_MK
	OUTPUT_MK := 1

h2:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::PHILO::\n$(RESET)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date\n$(RESET)" || true

endif