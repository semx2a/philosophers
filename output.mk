ifndef OUTPUT_MK
	OUTPUT_MK := 1

h2:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::PHILO::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date\n$(NO_COLOR)" || true

endif