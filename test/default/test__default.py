from pathlib import Path
from spl_core.test_utils.base_variant_test_runner import BaseVariantTestRunner


class Test_default(BaseVariantTestRunner):
    @property
    def component_paths(self):
        return [
            Path("components/calc"),
            Path("components/a"),
        ]

    @property
    def expected_build_artifacts(self):
        return []

    def test_build(self):
        pass

    def test_reports(self):
        pass
